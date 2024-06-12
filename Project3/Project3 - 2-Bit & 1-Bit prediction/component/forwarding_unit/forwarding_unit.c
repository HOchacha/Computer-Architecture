//
// Created by user on 2024-05-29.
//

#include "forwarding_unit.h"


FORWARD_CONTROL_OUT forwarding_unit(FORWARD_IN forward_in){

    FORWARD_CONTROL_OUT forward_control_out = {0,};

    // check rs dependency between ex stage and further stage
    // exclusive하게 forward 받을 데이터를 입력 받음
    if((forward_in.rs != 0) && (forward_in.rs == forward_in.ex_mem_write_index) && forward_in.control_mem.reg_write){
        forward_control_out.use_rs_data_from_ex_mem = 1;
    }
    else if ((forward_in.rs != 0) && (forward_in.rs == forward_in.mem_wb_write_index) && forward_in.control_wb.reg_write){
        forward_control_out.use_rs_data_from_mem_wb = 1;
    }
    else {}

    // check rt dependency between ex stage and further stage
    if((forward_in.rt != 0) && (forward_in.rt == forward_in.ex_mem_write_index) && forward_in.control_mem.reg_write){
        forward_control_out.use_rt_data_from_ex_mem = 1;
    }
    else if ((forward_in.rt != 0) && (forward_in.rt == forward_in.mem_wb_write_index) && forward_in.control_wb.reg_write){
        forward_control_out.use_rt_data_from_mem_wb = 1;
    }
    else {}

    return forward_control_out;
}
