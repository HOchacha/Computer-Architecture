//
// Created by user on 2024-05-30.
//

#include <stdint.h>

#ifndef COMPUTER_ARCHITECTURE_DECODE_TYPE_H
#define COMPUTER_ARCHITECTURE_DECODE_TYPE_H
typedef struct _decoded{
    uint32_t opcode :6;
    uint32_t rs: 5;
    uint32_t rt: 5;
    uint32_t rd: 5;
    uint32_t shamt : 5;
    uint32_t funct : 6;
    uint32_t imm : 16;
    uint32_t s_immediate : 32;
    uint32_t j_address : 26;
}Decoded_values;
#endif //COMPUTER_ARCHITECTURE_DECODE_TYPE_H
