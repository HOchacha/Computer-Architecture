#pragma once

#include <stdint.h>

#include "../../single_cycle/decode/decode_instruction.h"

#include "../control_unit/control_unit.h"


#ifndef REGISTER
#define REGISTER

#define STACK_INIT_ADDR 0x7fffffff

enum registers{$zero, $at,
        $v0, $v1,
        $a0, $a1, $a2, $a3,
        $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7,
        $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7,
        $t8, $t9,
        $k0, $k1,
        $gp,
        $sp,
        $fp,
        $ra,
};
typedef struct _register{
    uint32_t reg[32];
}Register;

typedef struct _register_input{
    uint32_t read_source;
    uint32_t read_target;
}Reg_in;

typedef struct _register_output{
    uint32_t reg1;
    uint32_t reg2;
}Reg_out;

Reg_out get_value_from_decoded_values(Reg_in register_in);
void set_register_from_input(uint32_t write_data, uint32_t write_address, uint32_t is_write, uint32_t is_upper_access);
#endif