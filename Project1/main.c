#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "register.h"
#include "instruction_cycle.h"
#define LOG
#define PRINT_ALL_REGISTER
#define TOTAL_LOG

speReg sr = { 0, };
genReg gr = { 0, };
const operators op = { "+", "-", "*", "/", "M", "B","C","GCD", "BEQ", "H" };

void printAllRegisterData();
void printALLSpecificData();
int main(int argc, char* args[]) {
    if (argc <= 1) {
        printf("Fatal Error : you need to specify input text file\n");
        return -1;
    }

    FILE* fp = fopen(args[1], "r");
    if (fp == NULL) {
        printf("Fatal Error : Fail to open input text files");
        return -1;
    }
    char buffer[100];


    // read all instructions for implement stored instruction machine
    char** instructionTable = calloc(100, sizeof(char*));

    int instructionMaxAddress = 0;
    while (fgets(buffer, 100, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        instructionTable[instructionMaxAddress] = (char*)malloc(strlen(buffer) + 1);
        if (instructionTable[instructionMaxAddress] == NULL) {
            printf("the instruction is already exist, check your source code please.\n");
            return -1;
        }
        strcpy(instructionTable[instructionMaxAddress], buffer);
        instructionMaxAddress++;
    }
#ifdef TOTAL_LOG
    printf("LOG : Instruction Loaded, initiate calculation\n");
#endif
    fclose(fp);
    fp = NULL;

    //configure specific register
    sr.programCounter = 0;
    while (1) {
        //gr, sr의 경우 extern을 이용하여 전역변수 공유할 수 있음
#ifdef LOG
        printf("LOG :: Fetch Instruction from %dth instruction\n", sr.programCounter);
#endif
        fetchInstruction(instructionTable);
#ifdef LOG
        printf("LOG :: Decode Instuction\n");
#endif
        decodeInstruction();

#ifdef LOG
        printf("LOG :: Execute Register Data\n");
#endif
        executeInstruction();

#ifdef LOG
        printf("LOG :: Write back result value to REG 0 \n");
#endif
        writeBackInstruction();
#ifdef PRINT_ALL_REGISTER
        printAllRegisterData();
#endif
        if (sr.trapFlag == 1) {
            printf("Fatal Error :: Trap triggered \n");
            break;
        }
        if (sr.haltFlag == 1) {
            printf("\nTERMINATION :: Terminate Calculator\n");
            break;
        }
#ifdef LOG
        printf("LOG :: Single Cycle Finished ::::::::::::::::::::\n\n\n");
#endif
#ifdef TOTAL_LOG
        printf("\n");
#endif
    }
    for (int i = 0; i < instructionMaxAddress; i++) {
        free(instructionTable[i]);
        instructionTable[i] = NULL;
    }
    printf("\nTERMINATION :: Calculator Ended\n");
    return 0;
}

void printAllRegisterData() {
    for (int i = 0; i < 10; i++) {
        printf("REG %d : %d\n", i, *getRegisterFromInteger(i));
    }
}
