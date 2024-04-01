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

// TODO: Loading the program with elf header required

// TODO: Make a Actual Driver Program for MIPS
//       Make sure that components of mips architecture have to be seperated each components.
//       Just recommend for making all components into functions.
//       Each Component is work as a kind of functions.
//       Enable(Control) Input, Architectural State(Register, Memory), Output Value


    return 0;
}