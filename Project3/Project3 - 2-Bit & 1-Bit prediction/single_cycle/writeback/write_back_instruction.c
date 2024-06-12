//
// Created by user on 2024-04-02.
//

#include "write_back_instruction.h"
#include "../../component/latch/latch.h"

uint32_t write_back_pipe(MEM_WB_SLOT latch_out){

    if(latch_out.invalid == 1) {
        return 0xFFFFFFFF;
    }

    uint32_t data_path_to_register = (latch_out.control.mem_to_reg) ?
                                    latch_out.mem_output.read_data : latch_out.alu_output.ALUresult;
    data_path_to_register = (latch_out.control.set_ra) ?
                            latch_out.pc_plus_4 + 4 : data_path_to_register;

    printf("PIPE :: write back : data = %08X, reg_idx = %08X, reg_write = %d, isUpperAccess = %d\n",
            data_path_to_register, latch_out.write_register_address, latch_out.control.reg_write, latch_out.control.isUpperAccess);

    set_register_from_input(data_path_to_register,
                            latch_out.write_register_address,
                            latch_out.control.reg_write,
                            latch_out.control.isUpperAccess);
    return latch_out.current_pc;
}

