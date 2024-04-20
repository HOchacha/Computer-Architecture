//
// Created by user on 2024-04-02.
//

#ifndef COMPUTER_ARCHITECTURE_MEMORY_H
#define COMPUTER_ARCHITECTURE_MEMORY_H
#define MEM_SIZE 0x8000000
// int를 기준으로, 구현하게 된다면 바이트 주소로 반드시 변환해야 한다.
typedef struct _memory{
    uint8_t mem[MEM_SIZE];
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
Memory_output set_input_memory_and_return_data(Memory_input inputs, Memory_control control_signals);
#endif //COMPUTER_ARCHITECTURE_MEMORY_H
