//
// Created by user on 2024-04-02.
//

#include "execute_instruction.h"
#include "../../component/latch/latch.h"
#include "../../component/forwarding_unit/forwarding_unit.h"


extern uint32_t PC;
extern Register general_reg;
EX_MEM_SLOT execute_instruction_pipe(ID_EX_SLOT id_ex_latch_out,
                                     EX_MEM_SLOT ex_mem_slot,
                                     MEM_WB_SLOT mem_wb_slot,
                                     IF_ID_LATCH* if_id_latch,
                                     ID_EX_LATCH* id_ex_latch,
                                     uint32_t* TERMINATION,
                                     branch_target_buffer* btb){



    if(id_ex_latch_out.invalid == 1){
        EX_MEM_SLOT ret = {0};
        ret.invalid = 1;
        ret.current_pc = 0xFFFFFFFF;
        return ret;
    }

    // execution
    Alu_control alu_control = get_ALU_operation(id_ex_latch_out.funct,
                                                id_ex_latch_out.control,
                                                id_ex_latch_out.opcode
                                                );

    // Forwarding Logic
    FORWARD_IN forward_in = {id_ex_latch_out.rs, id_ex_latch_out.rt,
                             ex_mem_slot.write_register_address,
                             mem_wb_slot.write_register_address,
                             ex_mem_slot.control,
                             mem_wb_slot.control};

    FORWARD_CONTROL_OUT forward_control_out = forwarding_unit(forward_in);

    uint32_t mem_to_reg_res = mem_wb_slot.control.mem_to_reg ?
                              mem_wb_slot.mem_output.read_data : mem_wb_slot.alu_output.ALUresult;


    // register out put value overwrite stage
    //=======================================================
    // use_rX_data_from_ex_mem |      0       |      1      |
    // use_rX_data_from_mem_wb |      1       |      0      | --> explicitly determined
    uint32_t forwarded_rs_value = (forward_control_out.use_rs_data_from_mem_wb ^ forward_control_out.use_rs_data_from_ex_mem) &&
                               (forward_control_out.use_rs_data_from_ex_mem) ? ex_mem_slot.alu_output.ALUresult : mem_to_reg_res;
    id_ex_latch_out.read_reg1 = (forward_control_out.use_rs_data_from_ex_mem ^ forward_control_out.use_rs_data_from_mem_wb) ?
                                    forwarded_rs_value : id_ex_latch_out.read_reg1;

    uint32_t forwarded_rt_value = (forward_control_out.use_rt_data_from_mem_wb ^ forward_control_out.use_rt_data_from_ex_mem) &&
                                  (forward_control_out.use_rt_data_from_ex_mem) ? ex_mem_slot.alu_output.ALUresult : mem_to_reg_res;
    id_ex_latch_out.read_reg2 = (forward_control_out.use_rt_data_from_ex_mem ^ forward_control_out.use_rt_data_from_mem_wb) ?
                                   forwarded_rt_value : id_ex_latch_out.read_reg2;

    if((forward_control_out.use_rs_data_from_mem_wb ^ forward_control_out.use_rs_data_from_ex_mem) &&
       (forward_control_out.use_rs_data_from_ex_mem)){
        printf("PIPE :: execute_instruction : rs forward trigger %08X", id_ex_latch_out.read_reg1);
    }

    if((forward_control_out.use_rt_data_from_mem_wb ^ forward_control_out.use_rt_data_from_ex_mem) &&
       (forward_control_out.use_rt_data_from_ex_mem)){
        printf("PIPE :: execute_instruction : rt forward trigger %08X", id_ex_latch_out.read_reg2);
    }


    printf("PIPE :: execute_instruction : operands (%08X, %08X)\n", id_ex_latch_out.read_reg1, id_ex_latch_out.read_reg2);

    // single cycle execution stage for setting alu input with multiplexer
    Alu_input alu_input = {0, };
    alu_input.operand1 = alu_control.isShift ?
                         id_ex_latch_out.read_reg2 : id_ex_latch_out.read_reg1;
    alu_input.operand2 = id_ex_latch_out.control.ALU_src ?
                         id_ex_latch_out.s_imm : id_ex_latch_out.read_reg2;
    alu_input.operand2 = alu_control.isShift ?
                         id_ex_latch_out.shamt : alu_input.operand2;
    alu_input.operand2 = id_ex_latch_out.control.isZeroExtend ?
                         id_ex_latch_out.imm : alu_input.operand2;
    Alu_output alu_output = do_arithmetic_operation(alu_input, alu_control);


    // Branch and Jump Processing
    uint32_t shift_left2_s_imm = id_ex_latch_out.s_imm << 2;
    uint32_t branch_addr = id_ex_latch_out.pc_plus_4 + shift_left2_s_imm;

    uint32_t jump_temp = id_ex_latch_out.jump_address << 2;
    uint32_t jump_addr = (id_ex_latch_out.pc_plus_4 & 0x80000000) | jump_temp;

    uint32_t jump_register = id_ex_latch_out.read_reg1;

    uint32_t isBranch = alu_output.isBranch &&
                        (id_ex_latch_out.control.isBNE || id_ex_latch_out.control.isBEQ);

    uint32_t npc = id_ex_latch_out.pc_plus_4;
    npc = isBranch ? branch_addr : npc;
    npc = id_ex_latch_out.control.jump ? jump_addr : npc;
    npc = id_ex_latch_out.control.isJR ? jump_register : npc;



    if(id_ex_latch_out.current_pc == 0x50){
        printf("Break Point\n");
    }


    // write back npc value to PC
    // JR
    // J
    // JAL
    // BRANCH (BNE/BEQ)
    if(id_ex_latch_out.control.isJR == 1 ||         // jr과 jalr 모두 커버
       id_ex_latch_out.control.jump == 1 ||         // j와 jal 모두 커버
       id_ex_latch_out.control.isBEQ ||
       id_ex_latch_out.control.isBNE)
    {
        if(id_ex_latch_out.control.isBEQ || id_ex_latch_out.control.isBNE){
            branch_correction correction = update_history_and_status(id_ex_latch_out.btb_index,
                                                                     btb,
                                                                     isBranch,
                                                                     id_ex_latch_out.current_pc,
                                                                     branch_addr);
            if(correction.is_mis_prediction){
                if_id_latch->slot[OUT_LATCH].invalid = 1;
                id_ex_latch->slot[OUT_LATCH].invalid = 1;
                PC = correction.revised_addr;
            }
        }else{ // JR, JAL, J, JALR에 해당
            PC = npc;
            if_id_latch->slot[OUT_LATCH].invalid = 1;
            id_ex_latch->slot[OUT_LATCH].invalid = 1;
        }

        if(npc == 0xFFFFFFFF){
            *TERMINATION = 1;
            if_id_latch->slot[OUT_LATCH].invalid = 1;
            id_ex_latch->slot[OUT_LATCH].invalid = 1;
        }
    }



    EX_MEM_SLOT ret = {id_ex_latch_out.pc_plus_4,
                       id_ex_latch_out.control,
                       npc,
                       alu_output,
                       id_ex_latch_out.read_reg2,
                       id_ex_latch_out.write_register_address,
                       id_ex_latch_out.invalid,
                       id_ex_latch_out.current_pc,
                       id_ex_latch_out.btb_index,
                       id_ex_latch_out.inst
    };

    return ret;
}