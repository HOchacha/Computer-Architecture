#pragma once

#include <stdint.h>
#include "../control_unit/control_unit.h"

#ifndef FORWARDING_UNIT
#define FORWARDING_UNIT
typedef struct _forward_in{
    uint32_t rs;
    uint32_t rt;
    uint32_t ex_mem_write_index;
    uint32_t mem_wb_write_index;
    CU_output control_mem;
    CU_output control_wb;
}FORWARD_IN;

typedef struct _forward_out{
    uint32_t use_rs_data_from_ex_mem;
    uint32_t use_rs_data_from_mem_wb;
    uint32_t use_rt_data_from_ex_mem;
    uint32_t use_rt_data_from_mem_wb;
}FORWARD_CONTROL_OUT;

FORWARD_CONTROL_OUT forwarding_unit(FORWARD_IN forward_in);
#endif