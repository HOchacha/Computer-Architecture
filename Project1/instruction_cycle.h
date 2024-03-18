//
// Created by user on 2024-03-18.
//

#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef COMPUTER_ARCHITECTURE_INSTRUCTION_CYCLE_H
#define COMPUTER_ARCHITECTURE_INSTRUCTION_CYCLE_H
void fetchInstruction(char ** instructionTable);
void decodeInstruction();
void fetchDataFromRegister();
void executeInstruction();

void setImmediateValueInRegister(uint32_t value, uint32_t* immediateRegister);
char *removePrefix(const char* str, const char* prefix);
uint32_t* getRegisterFromInteger(uint32_t index);
void setImmediateValueInRegister(uint32_t value, uint32_t* immediateRegister);
char *removePrefix(const char* str, const char* prefix);
void setOperatorReg(char** operator_reg, char* token);
uint32_t* getRegisterFromInteger(uint32_t index);
#endif //COMPUTER_ARCHITECTURE_INSTRUCTION_CYCLE_H
