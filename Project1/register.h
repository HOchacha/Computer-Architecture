//
// Created by user on 2024-03-18.
//

#ifndef STDINT
#include <stdint.h>
#endif

#ifndef COMPUTER_ARCHITECTURE_REGISTER_H
typedef struct generalRegisters {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
}genReg;

typedef struct specialRegisters {
    uint32_t programCounter;
    char* instructionReg;
    char* operatorReg;
    uint32_t sourceImmediateReg;
    uint32_t targetImmediateReg;
    uint32_t resultImmediateReg;
    uint32_t* sourceReg;
    uint32_t* targetReg;
    uint32_t* resultReg;
    int haltFlag;
    int trapFlag;
}speReg;

typedef struct _operators
{
    char* plus;
    char* minus;
    char* mult;
    char* div;
    char* move;
    char* branch;
    char* compare;
    char* halt;
}operators;

#define COMPUTER_ARCHITECTURE_REGISTER_H

#endif //COMPUTER_ARCHITECTURE_REGISTER_H
