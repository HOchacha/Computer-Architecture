//
// Created by user on 2024-04-02.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif
uint32_t sign_extender(uint16_t input_data){
    return (input_data >> 15) ? (((uint32_t)input_data)| 0xFFFF0000) : (uint32_t)input_data;
}
