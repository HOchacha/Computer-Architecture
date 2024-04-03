//
// Created by user on 2024-04-02.
//

#ifndef COMPUTER_ARCHITECTURE_MEMORY_H
#define COMPUTER_ARCHITECTURE_MEMORY_H


typedef struct _memory{
    char mem[0x800000000];
}Memory;

typedef struct _memory_input{
    uint32_t address;
    uint32_t write_data;
}Memory_input;

typedef struct _memory_control_signal{
    uint32_t mem_read;
    uint32_t mem_write;
}Memory_control;

typedef struct _memory_output{
    uint32_t read_data;
}Memory_output;

#endif //COMPUTER_ARCHITECTURE_MEMORY_H
