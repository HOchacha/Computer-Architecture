//
// Created by user on 2024-04-02.
//
#include <stdio.h>
#include "alu.h"
#define ALU_LOG
#define LOG

enum num{ADD_ALU = 0x20, ADDU_ALU = 0x21, SUB_ALU = 0x22, SUBU_ALU = 0x23,
    AND_ALU = 0x24, OR_ALU = 0x25,
    SLL_ALU = 0x0,
    SRL_ALU = 0x2, NOR_ALU = 0x27,
    SUB_EQ, SUB_NE,
    SLT_ALU = 0x2a, SLTU_ALU = 0x2b,
    LUI_ALU
};

// TODO: ALU 내부로 처리가 들어가고 있지 않음, ALU 컨트롤 시그널을 다루는 부분을 수정해야 할 필요가 있음
Alu_output do_arithmetic_operation(Alu_input alu_input, Alu_control alu_ops){
    Alu_output valueReturn = {0,};

    switch(alu_ops.funct){
        case ADD_ALU:
            valueReturn.ALUresult = (int32_t)alu_input.operand1 + (int32_t)alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : ADD_ALU");
#endif
            break;
        case ADDU_ALU:
            valueReturn.ALUresult = alu_input.operand1 + alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : ADDU_ALU");
#endif
            break;
        case SUB_ALU:
            valueReturn.ALUresult = (int32_t)alu_input.operand1 - (int32_t)alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : SUB_ALU");
#endif
            break;
        case SUBU_ALU:
            valueReturn.ALUresult = alu_input.operand1 - alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : SUBU_ALU");
#endif
            break;
        case LUI_ALU:
            valueReturn.ALUresult = alu_input.operand2 << 16;
#ifdef LOG
            printf("ALU OPS : LUI_ALU");
#endif
            break;
        case AND_ALU:
            valueReturn.ALUresult = alu_input.operand1 & alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : AND_ALU");
#endif
            break;
        case OR_ALU:
            valueReturn.ALUresult = alu_input.operand1 | alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : OR_ALU");
#endif
            break;
        case SLL_ALU:
            valueReturn.ALUresult = alu_input.operand1 << alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : SLL_ALU");
#endif
            break;
        case SRL_ALU:
            valueReturn.ALUresult = alu_input.operand1 >> alu_input.operand2;
#ifdef LOG
            printf("ALU OPS : SRL_ALU");
#endif
            break;
        case NOR_ALU:
            valueReturn.ALUresult = ~(alu_input.operand1 | alu_input.operand2);
#ifdef LOG
            printf("ALU OPS : NOR_ALU");
#endif
            break;
        case SUB_EQ:
            valueReturn.ALUresult = alu_input.operand1 - alu_input.operand2;
            valueReturn.isBranch = valueReturn.ALUresult ? 0 : 1;
#ifdef LOG
            printf("ALU OPS : SUB_EQ_ALU");
#endif
            break;
        case SUB_NE:
            valueReturn.ALUresult = alu_input.operand1 - alu_input.operand2;
            valueReturn.isBranch = valueReturn.ALUresult ? 1 : 0;
#ifdef LOG
            printf("ALU OPS : SUB_NE_ALU");
#endif
            break;

        case SLT_ALU:
            valueReturn.ALUresult = (int32_t)alu_input.operand1 < (int32_t)alu_input.operand2 ? 1 : 0;
#ifdef LOG
            printf("ALU OPS : SLT_ALU");
#endif
            break;
        case SLTU_ALU:
            valueReturn.ALUresult = alu_input.operand1 < alu_input.operand2 ? 1 : 0;
#ifdef LOG
            printf("ALU OPS : SLTU_ALU");
#endif
            break;
    }
#ifdef LOG
    printf("\nALU ops result : %08x\n", valueReturn.ALUresult);
#endif
    return valueReturn;
}

Alu_control get_ALU_operation(uint32_t funct, CU_output control, uint32_t opcode){
    Alu_control alu_control = {0,};
    if(control.ALU_op == 1) {
        switch(funct){
            case ADD_ALU:
                alu_control.funct = ADD_ALU;
                break;
            case ADDU_ALU:
                alu_control.funct = ADDU_ALU;
                break;
            case SUB_ALU:
                alu_control.funct = SUB_ALU;
                break;
            case SUBU_ALU:
                alu_control.funct = SUBU_ALU;
                break;
            case AND_ALU:
                alu_control.funct = AND_ALU;
                break;
            case NOR_ALU:
                alu_control.funct = NOR_ALU;
                break;
            case OR_ALU:
                alu_control.funct = OR_ALU;
                break;
            case SLL_ALU:
                alu_control.funct = SLL_ALU;
                alu_control.isShift = 1;
                break;
            case SRL_ALU:
                alu_control.funct = SRL_ALU;
                alu_control.isShift = 1;
                break;
            case SLT_ALU:
                alu_control.funct = SLT_ALU;
                break;
            case SLTU_ALU:
                alu_control.funct = SLTU_ALU;
                break;
            default:
                printf("No Proper Ops\n");
        }
    }
    //takes I type instruction
    if(control.ALU_op == 0 && control.isBEQ != 1 && control.isBNE != 1){
        alu_control.funct = ADDU_ALU;
    }
    //takes I type BEQ
    if(control.ALU_op == 0 && control.isBEQ == 1){
        alu_control.funct = SUB_EQ;
    }
    //takes I type BNE
    if(control.ALU_op == 0 && control.isBNE == 1){
        alu_control.funct = SUB_NE;
    }
    if(control.isSlt == 1){
        alu_control.funct = SLT_ALU;
    }
    if(control.isSltu == 1){
        alu_control.funct = SLTU_ALU;
    }
    if(control.isUpperAccess == 1){
        alu_control.funct = LUI_ALU;
    }
    if(ORI == opcode){
        alu_control.funct = OR_ALU;

    }
    if(ANDI == opcode){
        alu_control.funct = AND_ALU;
    }
    //printf("ALU_CONTROL : [%08X], isSHIFT : [%s]\n", alu_control.funct, alu_control.isShift ? "true" : "false");
    return alu_control;
}