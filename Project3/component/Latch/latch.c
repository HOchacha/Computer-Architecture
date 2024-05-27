//
// Created by user on 2024-05-11.
//

#include "latch.h"

void push_input_into_latch(){

}


void flush_IF_ID_LATCH(IF_ID_LATCH* latch){
    latch->slot[OUT_LATCH] = latch->slot[IN_LATCH];
    latch->slot[IN_LATCH] = latch->zero;
}

void flush_ID_EX_LATCH(ID_EX_LATCH* latch){
    latch->slot[OUT_LATCH] = latch->slot[IN_LATCH];
    latch->slot[IN_LATCH] = latch->zero;
}

void flush_EX_MEM_LATCH(EX_MEM_LATCH* latch){
    latch->slot[OUT_LATCH] = latch->slot[IN_LATCH];
    latch->slot[IN_LATCH] = latch->zero;
}

void flush_MEM_WB_LATCH(MEM_WB_LATCH* latch){
    latch->slot[OUT_LATCH] = latch->slot[IN_LATCH];
    latch->slot[IN_LATCH] = latch->zero;
}