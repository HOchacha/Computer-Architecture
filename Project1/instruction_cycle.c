#pragma warning(disable:4996)
#include <stdio.h>
#include "register.h"
#include <string.h>
#include <stdlib.h>
#include "instruction_cycle.h"

extern genReg gr;
extern speReg sr;
extern operators op;

void fetchInstruction(char** instructionTable) {
    sr.instructionReg = instructionTable[sr.programCounter++];
}

void decodeInstruction() {
    char* instructionBuffer = calloc(strlen(sr.instructionReg), 40);
    // copy the instruction from register
    strcpy(instructionBuffer, sr.instructionReg);
    printf("LOG :: instruction : %s\n", instructionBuffer);
    // set operator Register
    char* token = strtok(instructionBuffer, " ");
    setOperatorReg(&sr.operatorReg, token);

    // set source register
    token = strtok(NULL, " ");
    int temp = strncmp(token, "0x", 2);
    if (0 == temp) {
        // convert the string value to unsigned integer value
        char* temp = removePrefix(token, "0x");
        uint32_t value = strtoul(temp, NULL, 16);

        setImmediateValueInRegister(value, &sr.sourceImmediateReg);
        sr.sourceReg = &sr.sourceImmediateReg;
    }
    else if ((temp = strncmp(token, "R", 1)) == 0) {
        char* temp = removePrefix(token, "R");
        uint32_t value = strtoul(temp, NULL, 10);

        sr.sourceReg = getRegisterFromInteger(value);
    }

    token = strtok(NULL, " ");
    temp = strncmp(token, "0x", 2);
    if (0 == temp) {
        char* tempString = removePrefix(token, "0x");
        uint32_t value = strtoul(tempString, NULL, 16);

        setImmediateValueInRegister(value, &sr.targetImmediateReg);
        sr.targetReg = &sr.targetImmediateReg;
    }
    else if ((temp = strncmp(token, "R", 1)) == 0) {
        char* tempString = removePrefix(token, "R");
        uint32_t value = strtoul(tempString, NULL, 10);

        sr.targetReg = (uint32_t*)getRegisterFromInteger(value);
    }

    free(instructionBuffer);
    instructionBuffer = NULL;
}


// the function is slightly messy because of the gcd and BEQ operation.
void executeInstruction() {
    if (strcmp(sr.operatorReg, op.plus) == 0) {
        sr.resultImmediateReg = *sr.sourceReg + *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, op.minus) == 0) {
        sr.resultImmediateReg = *sr.sourceReg - *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, op.mult) == 0) {
        sr.resultImmediateReg = *sr.sourceReg * *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, op.div) == 0) {
        if (*sr.targetReg == 0) {
            sr.trapFlag = 1;
            return;
        }
        // 나눗셈 연산의 경우, 몫만을 가져오도록 구현함.
        sr.resultImmediateReg = *sr.sourceReg / *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, op.move) == 0) {
        *sr.sourceReg = *sr.targetReg;
    }
    else if (strcmp(sr.operatorReg, op.branch) == 0) {
        //this code block seem weird
        printf("TRIGGER :: LOG :: Branch Triggered : Operation B\n");
        sr.resultImmediateReg = *sr.sourceReg;
    }
    else if (strcmp(sr.operatorReg, op.compare) == 0) {
        if (*sr.sourceReg == *sr.targetReg) {
            sr.resultImmediateReg = 1;
        }
        else {
            sr.resultImmediateReg = 0;
        }
    }
    else if (strcmp(sr.operatorReg, op.gcd)==0)
    {
        // TODO: Implement GCD Operation by virtualizing the Computer API
        if(*sr.sourceReg <= 0 || *sr.targetReg <= 0)
        {
            sr.trapFlag = 1;
#ifdef LOG
            printf("Fatal error : the operand is not natural value\n");
#endif
            return;
        }
        uint32_t* tempSource = (uint32_t*)calloc(sizeof(uint32_t), 1);
        uint32_t* tempTarget = (uint32_t*)calloc(sizeof(uint32_t), 1);
        *tempSource = *sr.sourceReg;
        *tempTarget = *sr.targetReg;
        while (*tempTarget != 0)
        {
            uint32_t temp = *tempTarget;
            *tempTarget = *tempSource % *tempTarget;
            *tempSource = temp;
        }
        printf("LOG :: gcd result : %d", *tempSource);
        sr.resultImmediateReg = *tempSource;
        free(tempSource);
        free(tempTarget);
        tempSource = NULL;
        tempSource = NULL;
        return;
    }
    else if (strcmp(sr.operatorReg, op.beq)==0)
    {
        printf("TRIGGER :: LOG :: Branch Triggered : Operation BEQ\n");
        if(gr.r0 == *sr.sourceReg)
        {
            sr.programCounter = *sr.targetReg;
        }
    }
    else if (strcmp(sr.operatorReg, op.halt) == 0) {
        sr.haltFlag = 1;
    }
    else {
        sr.haltFlag = 1;
        sr.trapFlag = 1;
        return;
    }
}

void writeBackInstruction() {
    setResultTarget();
    if (strcmp(sr.operatorReg, op.branch) == 0) {
        sr.programCounter = sr.resultImmediateReg;
    }
    else {
        //C, +-*/,
        printf("LOG:: REG 0: %d, RES : %d\n", gr.r0, sr.resultImmediateReg);
        *sr.resultReg = sr.resultImmediateReg;
    }
}

void setResultTarget() {
    sr.resultReg = &gr.r0;
}

void setImmediateValueInRegister(uint32_t value, uint32_t* immediateRegister) {
    *immediateRegister = value;
}
uint32_t* getRegisterFromInteger(uint32_t index) {
    switch (index) {
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
char* removePrefix(const char* str, const char* prefix) {
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
    }
    else {
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
    else if (strcmp(token, op.compare) == 0)
    {
        *operator_reg = op.compare;
    }
    else if (strcmp(token, op.gcd) == 0)
    {
        *operator_reg = op.gcd;
    }
    else if (strcmp(token, op.beq) == 0)
    {
        *operator_reg = op.beq;
    }
    else if (strcmp(token, op.halt) == 0)
    {
        *operator_reg = op.halt;
    }
}
