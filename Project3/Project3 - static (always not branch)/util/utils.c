//
// Created by user on 2024-04-03.
//



#include "utils.h"

uint32_t byte_ordering(uint32_t data){
    uint32_t upp = (data << 24) & 0xff000000;
    uint32_t upp2 = (data << 8) & 0x00ff0000;
    uint32_t upp3 = (data >> 8) & 0x0000ff00;
    uint32_t upp4 = (data >> 24) & 0x000000ff;
    uint32_t inst = upp | upp2 | upp3 | upp4;
    return inst;
}