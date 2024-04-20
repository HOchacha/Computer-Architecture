//
// Created by user on 2024-04-02.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef DECODE_INSTRUCTION
#define DECODE_INSTRUCTION
#include "../../single_cycle/decode/decode_instruction.h"
#endif

#ifndef CU
#define CU
#include "../control_unit/control_unit.h"
#endif

#ifndef COMPUTER_ARCHITECTURE_REGISTER_H
#define COMPUTER_ARCHITECTURE_REGISTER_H
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
    uint32_t read_destination;
}Reg_in;
typedef struct _register_output{
    uint32_t reg1;
    uint32_t reg2;
}Reg_out;

typedef struct _register_control{
    uint32_t RegWrite;
}Reg_write;
#endif //COMPUTER_ARCHITECTURE_REGISTER_H

Reg_out get_value_from_input(Reg_in input, uint32_t is_write, uint32_t write_data);
Reg_out get_value_from_decoded_values(Decoded_values decoded_values, CU_output control_signal);
void set_register_with_write_data(uint32_t data_path, uint32_t regWrite);
