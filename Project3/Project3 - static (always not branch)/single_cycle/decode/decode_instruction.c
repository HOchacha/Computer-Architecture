#pragma once

#include "decode_instruction.h"


Decoded_values decode_instruction(uint32_t instruction){

    Decoded_values v = {0, };
    v.opcode = (instruction >> 26) & 0x3f;
    v.rs = (instruction >> 21) & 0x1f;
    v.rt = (instruction >> 16) & 0x1f;
    v.rd = (instruction >> 11) & 0x1f;
    v.shamt = (instruction >> 6) & 0x1f;
    v.funct = (instruction) & 0x3f;
    v.imm = (instruction) & 0xffff;
    v.s_immediate = sign_extend_16_to_32(v.imm);
    v.j_address = (instruction) & 0x03ffffff;

#ifdef LOG_DECODE_INSTRUCTION_INFO
    print_instruction_info(v);
#endif
    return v;
}

void print_instruction_info(Decoded_values v){
    printf("opcode : [0x%2X], RS : [%d], RT : [%d], RD : [%d], SHAMT : [%d], FUNCT : [0x%2X]\n",
           v.opcode, v.rs, v.rt, v.rd, v.shamt, v.funct);
    printf("imm : [0x%4x], j_addr : [0x%8X]\n", v.imm, v.j_address);
}

uint32_t sign_extend_16_to_32(uint16_t input_data){
    return (input_data >> 15) ? (((uint32_t)input_data)| 0xFFFF0000) : (uint32_t)input_data;
}

