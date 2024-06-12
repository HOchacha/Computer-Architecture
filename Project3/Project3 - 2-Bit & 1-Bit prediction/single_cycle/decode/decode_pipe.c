//
// Created by user on 2024-05-30.
//
#include "decode_pipe.h"
ID_EX_SLOT decode_instruction_pipe(IF_ID_SLOT if_id_latch_out){
    if(if_id_latch_out.invalid == 1){
        ID_EX_SLOT ret = {0};
        ret.invalid = 1;
        ret.current_pc = 0xFFFFFFFF;
        return ret;
    }

    printf("PIPE :: decode_instruction : %08x\n", if_id_latch_out.inst);
    // decode instruction
    Decoded_values decoded = decode_instruction(if_id_latch_out.inst);

    CU_input cu_opcode = {decoded.opcode, decoded.funct};
    CU_output control = set_control_signal(cu_opcode);

    uint32_t write_register_address = control.isItype ? decoded.rt : decoded.rd;
    write_register_address = control.set_ra ? 31 : write_register_address;

    // register access
    Reg_in register_in = {decoded.rs, decoded.rt};
    Reg_out reg_out = get_value_from_decoded_values(register_in);

    ID_EX_SLOT ret = {if_id_latch_out.pc_plus_4,
                      control,
                      decoded.opcode,
                      decoded.funct,
                      reg_out.reg1,
                      reg_out.reg2,
                      decoded.j_address,
                      decoded.shamt,
                      decoded.imm,
                      decoded.s_immediate,
                      decoded.rs,
                      decoded.rt,
                      write_register_address,
                      if_id_latch_out.invalid,
                      if_id_latch_out.current_pc,
                      if_id_latch_out.btb_index,
                      if_id_latch_out.inst
    };
    return ret;
}