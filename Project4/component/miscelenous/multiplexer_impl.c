//
// Created by user on 2024-04-12.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

uint32_t mux(uint32_t input_0, uint32_t input_1, uint32_t selection){
    return selection ? input_1 : input_0;
}