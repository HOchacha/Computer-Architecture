//
// Created by user on 2024-04-02.
//

#include "control_unit.h"
#include "../miscelenous/opcodes.h"
extern uint32_t number_of_instructions;
extern uint32_t number_R_type;
extern uint32_t number_I_type;
extern uint32_t number_J_type;
extern uint32_t number_memory_access;
extern uint32_t number_branch;

#define JR 0x08
CU_output set_control_signal(CU_input opcode){
    CU_output out = {0,};
    number_of_instructions++;
    if(opcode.opcode == R){
        number_R_type++;
        out.reg_dst = 1;
        out.ALU_op = 1;
    }
    if((opcode.opcode != 0) && ((opcode.opcode != J) && (opcode.opcode != JAL)))
    {
        number_I_type++;
    }

    if((opcode.opcode != 0) && (opcode.opcode != BEQ) && (opcode.opcode != BNE)){
        out.ALU_src = 1;
        out.isItype = 1;
    }
    if(opcode.opcode == LUI){
        out.isUpperAccess = 1;
    }
    if(opcode.opcode == LW) {
        out.mem_to_reg = 1;
    }
    if((opcode.opcode != SW) && (opcode.opcode != BEQ) && (opcode.opcode != BNE) && (opcode.opcode != J)){
        out.reg_write = 1;
    }
    if(opcode.opcode == LW){
        out.mem_read = 1;
    }
    if(opcode.opcode == SW){
        out.mem_write = 1;
    }
    if(opcode.opcode == BEQ){
        number_branch++;
        out.isBEQ = 1;
    }
    if(opcode.opcode == BNE){
        number_branch++;
        out.isBNE = 1;
    }
    if((0x08 == opcode.funct || 0x09 == opcode.funct) && R == opcode.opcode){
        out.isJR = 1;
    }
    if(J == opcode.opcode || JAL == opcode.opcode){
        number_J_type++;
        out.jump = 1;
    }
    // SLTI or SLT
    if(SLTI == opcode.opcode  || (0x2a == opcode.funct && R == opcode.opcode)){
        out.isSlt = 1;
    }
    // SLTIU or SLTU
    if(SLTIU == opcode.opcode || (0x2b == opcode.funct && R == opcode.opcode)){
        out.isSltu = 1;
    }
    if(JAL == opcode.opcode || (0x09 == opcode.funct && R == opcode.opcode)){
        out.set_ra = 1;
    }
    if(SW == opcode.opcode || LW == opcode.opcode){
        number_memory_access++;
    }
    if(ANDI == opcode.opcode || ORI == opcode.opcode){
        out.isZeroExtend = 1;
    }
    return out;
}