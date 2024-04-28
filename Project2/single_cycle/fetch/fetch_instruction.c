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
#include "../../component/memory/memory.h"
#endif
extern Register general_reg;
extern uint32_t PC;
extern Memory memory;

// TODO: Fetch Instruction에서는 명령어를 반환하도록 한다.
uint32_t fetch_instruction(uint32_t PC){
    printf("%08x\n", PC); 
    return get_instruction_from_address(PC);
}