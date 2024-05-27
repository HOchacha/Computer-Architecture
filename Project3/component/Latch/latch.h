//
// Created by user on 2024-05-11.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef SINGLE_CYCLE
#define SINGLE_CYCLE
#include "../../single_cycle/decode/decode_instruction.h"


#endif

#ifndef COMPONENT
#define COMPONENT
#include "../control_unit/control_unit.h"
#include "../register/register.h"
#include "../alu/alu.h"
#include "../memory/memory.h"

#endif

#ifndef COMPUTER_ARCHITECTURE_LATCH_H
#define COMPUTER_ARCHITECTURE_LATCH_H

#define IN_LATCH 1
#define OUT_LATCH 0

typedef struct _if_id{
    uint32_t pc_plus_4;

    uint32_t inst;
}IF_ID_SLOT;

typedef struct _id_ex{
    uint32_t pc_plus_4;
    CU_output control;
    
    uint32_t opcode;
    uint32_t funct;

    // if jr, use rs of reg_out
    Reg_out reg_out;

    uint32_t jump_address;
    uint32_t shamt;
    uint32_t s_imm;

    // propagate until wb
    uint32_t write_register_address;
}ID_EX_SLOT;

typedef struct _ex_mem{
    CU_output control;
    uint32_t pc_plus_4;

    Alu_output alu_output;
    uint32_t rt_v;

    // Write back index
    uint32_t write_register_address;
}EX_MEM_SLOT;

typedef struct _mem_wb{
    CU_output control;
    uint32_t pc_plus_4;

    Alu_output alu_output;
    Memory_output mem_output;

    // Write back index
    uint32_t write_register_address;
}MEM_WB_SLOT;


// latch struct definition
typedef struct _if_id_latch{
    uint32_t invalid;

    IF_ID_SLOT slot[2];
    const IF_ID_SLOT zero;
}IF_ID_LATCH;

typedef struct _id_ex_latch{
    uint32_t invalid;

    ID_EX_SLOT slot[2];
    const ID_EX_SLOT zero;
}ID_EX_LATCH;

typedef struct _ex_mem_latch{
    uint32_t invalid;

    EX_MEM_SLOT slot[2];
    const EX_MEM_SLOT zero;
}EX_MEM_LATCH;

typedef struct _mem_wb_latch{
    uint32_t invalid;

    MEM_WB_SLOT slot[2];
    const MEM_WB_SLOT zero;
}MEM_WB_LATCH;

void flush_IF_ID_LATCH(IF_ID_LATCH* latch);
void flush_ID_EX_LATCH(ID_EX_LATCH* latch);
void flush_EX_MEM_LATCH(EX_MEM_LATCH* latch);
void flush_MEM_WB_LATCH(MEM_WB_LATCH* latch);

#endif //COMPUTER_ARCHITECTURE_LATCH_H
