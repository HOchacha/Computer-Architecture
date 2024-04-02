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


// TODO: Loading the program with elf header required

    unsigned char elf_header[0x40];
    fread(elf_header, 1, 0x40, file);
    printf("\n");
    if (elf_header[0] != 0x7f || elf_header[1] != 'E' || elf_header[2] != 'L' || elf_header[3] != 'F') {
        printf("Error: %s is not an ELF file with incorrect start byte sequence\n", args[1]);
        for (int i = 0; i < 4; i++) {
            printf("%02x ", elf_header[i]);
        }
        printf("\n");
        return 0;
    }
    uint16_t elf_version = elf_header[0x04];
    uint32_t elf_shoff = *((uint32_t*)(elf_header + 0x20));


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