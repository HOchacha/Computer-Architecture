//
// Created by user on 2024-04-02.
//

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif
#include "memory.h"

uint32_t get_instruction_from_address(){

    return 0;
}

// this function process Read and Write at the same time
// Not likely, Register, Memeory is not working in several steps.
// So, we don't need to seperate the operation of the component
Memory_output set_input_memory_and_return_data(Memory_input inputs, Memory_control control_signals){


}

