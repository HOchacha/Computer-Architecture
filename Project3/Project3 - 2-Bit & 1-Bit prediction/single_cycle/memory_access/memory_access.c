#include "memory_access.h"

MEM_WB_SLOT memory_access_pipe(EX_MEM_SLOT latch_out){
    if(latch_out.invalid == 1){
        MEM_WB_SLOT ret = {0};
        ret.invalid = 1;
        ret.current_pc = 0xFFFFFFFF;
        return ret;
    }
    Memory_input mem_input = {latch_out.alu_output.ALUresult,
                              latch_out.rt_v};

    Memory_control mem_control = {latch_out.control.mem_read,
                                  latch_out.control.mem_write};
    printf("PIPE :: %08x :: memory access : Address = %08X, Reg2 = %08X\n", latch_out.inst,latch_out.alu_output.ALUresult, latch_out.rt_v);
    Memory_output mem_output = set_input_memory_and_return_data(mem_input, mem_control);


    MEM_WB_SLOT ret = {latch_out.pc_plus_4,
                       latch_out.control,
                       latch_out.alu_output,
                       mem_output,
                       latch_out.write_register_address,
                       0,
                       latch_out.current_pc,
                       latch_out.btb_index,
                       latch_out.inst};

    return ret;
}