//
// Created by user on 2024-04-02.
//
#include <stdio.h>
#include "fetch_instruction.h"
#include "../../component/register/register.h"
#define LOG
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif
#ifndef MEMORY_H
#define MEMORY_H
#include "../../component/memory/memory.h"
#include "../../component/cache/cache_memory.h"
#endif

extern Register general_reg;
extern uint32_t PC;
extern Memory memory;

// TODO: Fetch Instruction에서는 명령어를 반환하도록 한다.
uint32_t fetch_instruction(uint32_t PC){
    //printf("%08x\n", PC);
    return get_instruction_from_address(PC);
}

uint32_t fetch_instruction_from_cache(uint32_t address){
    // fetch instruction call statically read memory function
    uint32_t ret = do_cache_manipulation(0, address, 0, 1);
    printf(":::CACHE-ACCESS::: PC: %08x, INST: %08x\n", address, ret);

    return ret;
}