//
// Created by user on 2024-04-02.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif
#ifndef COMPUTER_ARCHITECTURE_FETCH_INSTRUCTION_H
#define COMPUTER_ARCHITECTURE_FETCH_INSTRUCTION_H

//PC의 경우, Architectural State이므로 전역 변수로 접근하도록 한다.
uint32_t fetch_instruction();
#endif //COMPUTER_ARCHITECTURE_FETCH_INSTRUCTION_H

