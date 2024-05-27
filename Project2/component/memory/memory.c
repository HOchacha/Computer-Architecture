//
// Created by user on 2024-04-02.
//

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif
#include "memory.h"
#define LOG
#include <stdio.h>

extern Memory memory;


uint32_t get_instruction_from_address(uint32_t PC){
    //printf("PC : %08x\n", PC);
    uint32_t temp = *(uint32_t*)(memory.mem + (PC));

    return temp;
}

// This function process Read and Write at the same time
// Not likely, Register, Memeory is not working in several steps.
// So, we don't need to seperate the operation of the component
Memory_output set_input_memory_and_return_data(Memory_input inputs, Memory_control control_signals){
    Memory_output valueHolder = {0,};
    //printf("\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\n");
    if (control_signals.mem_write == 1){
#ifdef LOG
        printf("MEMORY WRITE : MEM[%08x] = %08x\n", inputs.address, inputs.write_data);
#endif
        if(inputs.address > 0x7FFFFFFF){
            return valueHolder;
        }
        *((uint32_t*)(memory.mem + inputs.address)) = inputs.write_data;
    }
    if (control_signals.mem_read == 1){
#ifdef LOG
        printf("MEMORY READ : MEM[%08x] = %08x\n", inputs.address, *((uint32_t*)(memory.mem + inputs.address)));
#endif
        if(inputs.address > 0x7FFFFFFF){
            return valueHolder;
        }
        valueHolder.read_data = *((uint32_t*)(memory.mem + inputs.address));
    }
    //printf("\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\'\n");
    return valueHolder;
}

uint32_t get_memory_value_from_input(uint32_t address){
    return *((uint32_t*)(memory.mem + address));
}
