//
// Created by user on 2024-04-02.
//

#include "fetch_instruction.h"
#include "../../component/register/register.h"

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

extern Register reg;
extern uint32_t PC;
extern uint32_t mem[];
// TODO: Fetch Instruction에서는 명령어를 반환하도록 한다.
uint32_t fetch_instruction(){
    return get_instruction_from_address();
}