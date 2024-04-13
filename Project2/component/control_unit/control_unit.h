//
// Created by user on 2024-04-02.
//

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef COMPUTER_ARCHITECTURE_CONTROL_UNIT_H
#define COMPUTER_ARCHITECTURE_CONTROL_UNIT_H
typedef struct _control_unit_input{
    uint32_t opcode;
}CU_input;

typedef struct _control_unit_output{
    uint32_t reg_dst;
    uint32_t jump;
    uint32_t branch;
    uint32_t mem_read;
    uint32_t mem_to_reg;
    uint32_t ALU_op;
    uint32_t mem_write;
    uint32_t ALU_src;
    uint32_t reg_write;
}CU_output;
#endif //COMPUTER_ARCHITECTURE_CONTROL_UNIT_H


