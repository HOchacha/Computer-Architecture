//
// Created by user on 2024-04-02.
//

#include "fetch_instruction.h"
#include "../../component/register/register.h"

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif
#ifndef MEMORY_H
#define MEMORY_H

#endif
extern Register general_reg;
extern uint32_t PC;
extern Memory memory;

// TODO: Fetch Instruction에서는 명령어를 반환하도록 한다.
uint32_t fetch_instruction(uint32_t PC){
    //printf("%08x\n", PC);
    return get_instruction_from_address(PC);
}

IF_ID_SLOT fetch_instruction_pipe(uint32_t pc, uint32_t termination){
    if(termination == 1){
        printf("PIPE :: Fetch instruction : TERMINATION\n");
        IF_ID_SLOT ret = {0,0,1,pc};
        return ret;
    }

    uint32_t npc = pc + 4;
    // memory access for instruction
    uint32_t instruction = get_instruction_from_address(pc);
    PC = PC + 4;
    printf("PIPE :: Fetch instruction : %08X\n", instruction);

    IF_ID_SLOT ret = {npc, instruction, 0, pc};

    return ret;
}