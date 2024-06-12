#pragma once
#include <stdint.h>
#include "../control_unit/control_unit.h"

#ifndef ALU
#define ALU
typedef struct _alu_input{
    uint32_t operand1;
    uint32_t operand2;
    uint32_t ALUops;
}Alu_input;

typedef struct _alu_output{
    uint32_t ALUresult;
    uint32_t isBranch;
}Alu_output;

typedef struct _alu_control{
    uint32_t funct;
    uint32_t isShift;
}Alu_control;


Alu_output do_arithmetic_operation(Alu_input alu_input, Alu_control alu_control);
enum opcode{R = 0x0,
    ADDI = 0x8, ADDIU = 0x9,
    ANDI = 0xC,
    BEQ = 0x4, BNE = 0x5,
    J = 0x2, JAL = 0x3,
    // LBU = 0x24, LHU = 0x25,
    // LL = 0x30, LUI = 0xF
    LW = 0x23, ORI = 0xd,
    SLTI = 0xA, SLTIU = 0xb,
    // SB = 0x28, SC = 0x38, SH = 0x29,
    SW = 0x2b
};

enum funct{ADD = 0x20, ADDU = 0x21,
    AND = 0x24, //JR   = 0x08, (NO takes ALU)
    NOR = 0x27, OR   = 0x25,
    SLT = 0x2A, SLTU = 0x2B,
    SLL = 0x00, SRL  = 0x02,
    SUB = 0x22, SUBU = 0x23

};

Alu_control get_ALU_operation(uint32_t funct, CU_output control, uint32_t opcode);
#endif