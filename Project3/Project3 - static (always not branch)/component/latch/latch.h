#pragma once

#include <stdint.h>

#include "../control_unit/control_unit.h"
#include "../register/register.h"
#include "../alu/alu.h"
#include "../memory/memory.h"
#include "../../component/latch/latch.h"

#define IN_LATCH 1
#define OUT_LATCH 0


#ifndef LATCH
#define LATCH
typedef struct if_id{
    uint32_t pc_plus_4;
    uint32_t inst;

    uint32_t invalid;
    uint32_t current_pc;
}IF_ID_SLOT;

typedef struct ex_mem{
    uint32_t pc_plus_4;
    CU_output control;
    uint32_t n_pc;

    Alu_output alu_output;
    uint32_t rt_v;

    // Write back index
    uint32_t write_register_address;
    uint32_t invalid;
    uint32_t current_pc;
}EX_MEM_SLOT;

typedef struct mem_wb{
    uint32_t pc_plus_4;
    CU_output control;


    Alu_output alu_output;
    Memory_output mem_output;

    // Write back index
    uint32_t write_register_address;
    uint32_t invalid;
    uint32_t current_pc;
}MEM_WB_SLOT;

typedef struct id_ex{
    uint32_t pc_plus_4;
    CU_output control;

    uint32_t opcode;
    uint32_t funct;


    uint32_t read_reg1;
    uint32_t read_reg2;

    uint32_t jump_address;
    uint32_t shamt;
    uint32_t imm;
    uint32_t s_imm;

    uint32_t rs;
    uint32_t rt;

    // propagate until wb
    uint32_t write_register_address;
    uint32_t invalid;
    uint32_t current_pc;
}ID_EX_SLOT;

// latch struct definition
typedef struct if_id_latch{
    uint32_t invalid;

    IF_ID_SLOT slot[2];
    const IF_ID_SLOT zero;
}IF_ID_LATCH;

typedef struct id_ex_latch{
    uint32_t invalid;

    ID_EX_SLOT slot[2];
    const ID_EX_SLOT zero;
}ID_EX_LATCH;

typedef struct ex_mem_latch{
    uint32_t invalid;

    EX_MEM_SLOT slot[2];
    const EX_MEM_SLOT zero;
}EX_MEM_LATCH;

typedef struct mem_wb_latch{
    uint32_t invalid;

    MEM_WB_SLOT slot[2];
    const MEM_WB_SLOT zero;
}MEM_WB_LATCH;

void flush_IF_ID_LATCH(IF_ID_LATCH* latch);
void flush_ID_EX_LATCH(ID_EX_LATCH* latch);
void flush_EX_MEM_LATCH(EX_MEM_LATCH* latch);
void flush_MEM_WB_LATCH(MEM_WB_LATCH* latch);

void push_IF_ID_LATCH(IF_ID_LATCH* latch, IF_ID_SLOT slot);
void push_ID_EX_LATCH(ID_EX_LATCH* latch, ID_EX_SLOT slot);
void push_EX_MEM_LATCH(EX_MEM_LATCH* latch, EX_MEM_SLOT slot);
void push_MEM_WB_LATCH(MEM_WB_LATCH* latch, MEM_WB_SLOT slot);

IF_ID_SLOT conditional_latch_out_IF_ID(IF_ID_LATCH* latch);
ID_EX_SLOT conditional_latch_out_ID_EX(ID_EX_LATCH* latch);
EX_MEM_SLOT conditional_latch_out_EX_MEM(EX_MEM_LATCH* latch);
MEM_WB_SLOT conditional_latch_out_MEM_WB(MEM_WB_LATCH* latch);
#endif