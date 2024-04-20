//
// Created by user on 2024-04-02.
//

#include "control_unit.h"
enum _opcode{R = 0x0,
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
#define JR 0x08
CU_output set_control_signal(CU_opcode opcode){
    CU_output out = {0};
    if(opcode.opcode == R){
        out.reg_dst = 1;
    }
    if((opcode.opcode != 0) && (opcode.opcode != BEQ) && (opcode.opcode != BNE)){
        out.ALU_src = 1;
    }
    if(opcode.opcode == LW) {
        out.mem_to_reg = 1;
    }
    if((opcode.opcode != SW) && (opcode.opcode != BEQ) && (opcode.opcode != BNE) && (opcode.opcode != J) && (opcode.opcode == R && opcode.funct == JR)){
        out.reg_write = 1;
    }
    if(opcode.opcode == LW){
        out.mem_read = 1;
    }
    if(opcode.opcode == SW){
        out.mem_write = 1;
    }
              
    return out;
}