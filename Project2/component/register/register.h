//
// Created by user on 2024-04-02.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef COMPUTER_ARCHITECTURE_REGISTER_H
#define COMPUTER_ARCHITECTURE_REGISTER_H
typedef struct _register{
    uint32_t reg[32];
}Register;

typedef struct _register_input{
    uint32_t read_source;
};
typedef struct _register_output{
    uint32_t reg1;
    uint32_t reg2;
}Reg_out;
#endif //COMPUTER_ARCHITECTURE_REGISTER_H

Reg_out get_value_from_input(uint32_t read_reg1, uint32_t read_reg2, uint32_t write_reg, uint32_t is_write, uint32_t write_data);
uint32_t* get_register_from_integer(uint32_t reg_integer);