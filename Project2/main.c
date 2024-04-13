//
// Created by user on 2024-04-02.
//

//define all macros
#define LOG


#ifndef STANDARD_HEADER
#define STANDARD_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#endif

int main(int arg, char* args[]){

    if(arg <= 1){
#ifdef LOG
        printf("no specified argument for program input\n");
#endif
    }

    FILE* file = fopen(args[1], "rb");
    if (file == NULL){
#ifdef LOG
        printf("Cannot Open the specified file\n");
#endif
    }
    uint32_t buff;
    while(fread(&buff, sizeof(uint32_t), 1, file) ==1){
        printf("%x\n", buff);
    }
    fclose(file);

// TODO: the instruction file will be fed on this program.
//       there is no any header

// 파일을 읽어들일 때는 Byte Ordering에 따라서, 적절하게 값을 메모리에 로드할 수 있도록 한다.
// 명령어를 받을 때는, PC를 4로 값을 나눠서 접근할 수 있도록 한다.

// TODO: Make a Actual Driver Program for MIPS
//       Make sure that components of mips architecture have to be seperated each components.
//       Just recommend for making all components into functions.
//       Each Component is work as a kind of functions.
//       Enable(Control) Input, Architectural State(Register, Memory), Output Value

// TODO: init register values
//       all the register have to be initialized with 0x0
//       LR(r31) have to be initialized with 0xFFFF:FFFF
//       -> if PC become 0xFFFF:FFFF, then machine complete execution
//       SP(r29) have to be initialized with 0x1000:0000

// Q: do we have to implement lock?

/*

 Some of the processing logic in program

*/



// TODO: the end of the program, machine have to set v0 value
//       the value of the register must be printed out
//       i. Final return value (value in r2) – up to here, basic requirement
//       ii. Number of executed instructions
//       iii. Number of (executed) R-type instruction
//       iv. Number of I-type instruction
//       v. Number of J-type instruction
//       vi. Number of memory access instructions
//       vii. Number of taken branches

    return 0;
}