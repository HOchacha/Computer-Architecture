#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "register.h"
#include "instruction_cycle.h"
speReg sr = {0,};
genReg gr = {0,};
operators op = { "+", "-", "*", "/", "M", "B", "H" };
void printAllRegisterData();
void printALLSpecificData();
int main(int argc, char* args[]) {
    if (argc <= 1) {
        printf("Fatal Error : you need to specify input text file\n");
        return -1;
    }

    FILE *fp = fopen(args[1], "r");
    if (fp == NULL) {
        printf("Fail to open input text files");
        return -1;
    }
    char buffer[100];


    // read all instructions for implement stored instruction machine
    char **instructionTable = calloc(100, sizeof(char *));

    int instructionMaxAddress = 0;
    while (fgets(buffer, 100, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        instructionTable[instructionMaxAddress] = (char *) malloc(strlen(buffer) + 1);
        if (instructionTable[instructionMaxAddress] == NULL) {
            printf("the instruction is already exist, check your source code please.\n");
            return -1;
        }
        strcpy(instructionTable[instructionMaxAddress], buffer);
        instructionMaxAddress++;
    }

    fclose(fp);
    fp = NULL;

    //configure specific register
    sr.programCounter = 0;
    while (1) {
        //gr, sr의 경우 extern을 이용하여 전역변수 공유할 수 있음
        printf("LOG :: Fetch Instruction\n");
        fetchInstruction(instructionTable);

        printf("LOG :: Decode Instuction\n");
        decodeInstruction();

        printf("LOG :: Fetch Register Data\n");
        fetchDataFromRegister();

        printf("LOG :: Execute Register Data\n");
        executeInstruction();

        printAllRegisterData();
        if (sr.haltFlag == 1) {
            printf("Terminate Calculator");
            break;
        }
        printf("LOG :: Single Cycle Finished ::::::::::::::::::::\n\n\n");
    }
    for (int i = 0; i < instructionMaxAddress; i++) {
        free(instructionTable[i]);
        instructionTable[i] = NULL;
    }
    printf("LOG :: Calculator Ended\n");
    return 0;
}

void printAllRegisterData(){
    for(int i = 0; i < 10; i++){
        printf("REG %d : %d\n", i,*getRegisterFromInteger(i));
    }
}