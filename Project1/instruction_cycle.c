#pragma warning(disable:4996)
#include <stdio.h>
#include "register.h"
#include <string.h>
#include <stdlib.h>
#include "instruction_cycle.h"

extern genReg gr;
extern speReg sr;
extern operators op;


void fetchInstruction(char ** instructionTable){
    sr.instructionReg = instructionTable[sr.programCounter++];
}

// instruction buffer and token is the heap memory.
// watch out for using them.
void decodeInstruction(){
    char* instructionBuffer = calloc(strlen(sr.instructionReg),40);
    // copy the instruction from register
    strcpy(instructionBuffer, sr.instructionReg);
    printf("LOG :: instruction : %s\n", instructionBuffer);
    // set operator Register
    char * token = strtok(instructionBuffer, " ");
    setOperatorReg(&sr.operatorReg, token);

    // set source register
    token = strtok(NULL, " ");
    int temp = strncmp(token, "0x", 2);
    if (0 == temp){
        // convert the string value to unsigned integer value
        char* temp = removePrefix(token, "0x");
        uint32_t value = strtoul(temp, NULL, 10);

        setImmediateValueInRegister(value , &sr.sourceImmediateReg);
        sr.sourceReg = &sr.sourceImmediateReg;
    }
    else if((temp = strncmp(token, "R",1)) == 0) {
        char* temp = removePrefix(token, "R");
        uint32_t value = strtoul(temp, NULL, 10);

        sr.sourceReg = getRegisterFromInteger(value);
    }

    // set target register
    token = strtok(NULL, " ");
    temp = strncmp(token, "0x", 2);
    if (0 == temp) {
        char* temp = removePrefix(token, "0x");
        uint32_t value = strtoul(temp, NULL, 10);

        setImmediateValueInRegister(value, &sr.targetImmediateReg);
        sr.targetReg = &sr.targetImmediateReg; 
    }
    else if((temp = strncmp(token, "R",1)) == 0){
        char* temp = removePrefix(token, "R");
        uint32_t value = strtoul(temp, NULL, 10);

        sr.targetReg = (uint32_t *) getRegisterFromInteger(value);
    }

    free(instructionBuffer);
    instructionBuffer = NULL;
}

void fetchDataFromRegister(){
    //there is no data-fetch steps in the cycle
}

void executeInstruction(){
    if(strcmp(sr.operatorReg, "+")==0){
        gr.r0 = *sr.sourceReg + *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, "-")==0){
        gr.r0 = *sr.sourceReg - *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, "*")==0){
        gr.r0 = *sr.sourceReg * *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, "/")==0){
        if (sr.targetReg == 0) {
            sr.trapFlag = 1;
            return;
        }
        gr.r0 = *sr.sourceReg / *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, "M")==0){
        *sr.sourceReg = *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, "B")==0){

    }
    else if (strcmp(sr.operatorReg, "H")==0){
        sr.haltFlag = 1;
    }
    else {
        sr.haltFlag = 1;
        sr.trapFlag = 1;
        return;
    }
}

void setImmediateValueInRegister(uint32_t value, uint32_t* immediateRegister) {
    *immediateRegister = value;
}
uint32_t* getRegisterFromInteger(uint32_t index){
    switch (index){
        case 0:
            return &(gr.r0);
        case 1:
            return &(gr.r1);
        case 2:
            return &(gr.r2);
        case 3:
            return &(gr.r3);
        case 4:
            return &(gr.r4);
        case 5:
            return &(gr.r5);
        case 6:
            return &(gr.r6);
        case 7:
            return &(gr.r7);
        case 8:
            return &(gr.r8);
        case 9:
            return &(gr.r9);
        default:
            return NULL;
    }
}
char *removePrefix(const char* str, const char* prefix) {
    size_t lenStr = strlen(str);
    size_t lenPrefix = strlen(prefix);

    if (strncmp(str, prefix, lenPrefix) == 0) {

        size_t newStrLen = lenStr - lenPrefix + 1;

        char* newStr = (char*)malloc(newStrLen);
        if (newStr == NULL) {
            printf("Memory allocation failed\n");
            return NULL;
        }

        strcpy(newStr, str + lenPrefix);

        return newStr;
    } else {
        char* newStr = (char*)malloc(lenStr + 1);
        if (newStr == NULL) {
            printf("Memory allocation failed\n");
            return NULL;
        }
        strcpy(newStr, str);
        return newStr;
    }
}

void setOperatorReg(char** operator_reg, char* token)
{
    if (strcmp(token, op.plus) == 0)
    {
        *operator_reg = op.plus;
    }
    else if (strcmp(token, op.minus) == 0)
    {
        *operator_reg = op.minus;
    }
    else if (strcmp(token, op.mult) == 0)
    {
        *operator_reg = op.mult;
    }
    else if (strcmp(token, op.div) == 0)
    {
        *operator_reg = op.div;
    }
    else if (strcmp(token, op.branch) == 0)
    {
        *operator_reg = op.branch;
    }
    else if (strcmp(token, op.move) == 0)
    {
        *operator_reg = op.move;
    }
    else if (strcmp(token, op.halt) == 0)
    {
        *operator_reg = op.halt;
    }
}
