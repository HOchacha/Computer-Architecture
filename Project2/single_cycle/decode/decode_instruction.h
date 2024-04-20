//
// Created by user on 2024-04-02.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif
#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif
#ifndef COMPUTER_ARCHITECTURE_DECODE_INSTRUCTION_H
#define COMPUTER_ARCHITECTURE_DECODE_INSTRUCTION_H
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

Decoded_values decode_instruction(uint32_t);
#endif //COMPUTER_ARCHITECTURE_DECODE_INSTRUCTION_H

uint32_t sign_extend_16_to_32(uint16_t input_data);