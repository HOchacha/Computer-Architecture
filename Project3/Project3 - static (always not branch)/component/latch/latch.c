#include "latch.h"


void flush_IF_ID_LATCH(IF_ID_LATCH* latch){
    latch->slot[IN_LATCH] = latch->slot[OUT_LATCH];
    latch->slot[OUT_LATCH] = latch->zero;
    latch->invalid = 0;
}

void flush_ID_EX_LATCH(ID_EX_LATCH* latch){
    latch->slot[IN_LATCH] = latch->slot[OUT_LATCH];
    latch->slot[OUT_LATCH] = latch->zero;
    latch->invalid = 0;
}

void flush_EX_MEM_LATCH(EX_MEM_LATCH* latch){
    latch->slot[IN_LATCH] = latch->slot[OUT_LATCH];
    latch->slot[OUT_LATCH] = latch->zero;
    latch->invalid = 0;
}

void flush_MEM_WB_LATCH(MEM_WB_LATCH* latch){
    latch->slot[IN_LATCH] = latch->slot[OUT_LATCH];
    latch->slot[OUT_LATCH] = latch->zero;
    latch->invalid = 0;
}

void push_IF_ID_LATCH(IF_ID_LATCH* latch, IF_ID_SLOT slot){
    latch->slot[OUT_LATCH] = slot;
}

void push_ID_EX_LATCH(ID_EX_LATCH* latch, ID_EX_SLOT slot){
    latch->slot[OUT_LATCH] = slot;
}

void push_EX_MEM_LATCH(EX_MEM_LATCH* latch, EX_MEM_SLOT slot){
    latch->slot[OUT_LATCH] = slot;
}

void push_MEM_WB_LATCH(MEM_WB_LATCH* latch, MEM_WB_SLOT slot){
    latch->slot[OUT_LATCH] = slot;
}

IF_ID_SLOT conditional_latch_out_IF_ID(IF_ID_LATCH* latch){
     if(latch->slot[IN_LATCH].invalid == 1){
         IF_ID_SLOT invalidated_slot = latch->zero;
         invalidated_slot.invalid = 1;
         return invalidated_slot;
     }
     else{
         return latch->slot[IN_LATCH];
     }
}

ID_EX_SLOT conditional_latch_out_ID_EX(ID_EX_LATCH* latch){
    if(latch->slot[IN_LATCH].invalid == 1){
        ID_EX_SLOT invalidated_slot = latch->zero;
        invalidated_slot.invalid = 1;
        return invalidated_slot;
    }
    else{
        return latch->slot[IN_LATCH];
    }
}

EX_MEM_SLOT conditional_latch_out_EX_MEM(EX_MEM_LATCH* latch){
    if(latch->slot[IN_LATCH].invalid == 1){
        EX_MEM_SLOT invalidated_slot = latch->zero;
        invalidated_slot.invalid = 1;
        return invalidated_slot;
    }
    else{
        return latch->slot[IN_LATCH];
    }
}

MEM_WB_SLOT conditional_latch_out_MEM_WB(MEM_WB_LATCH* latch){
    if(latch->slot[IN_LATCH].invalid == 1){
        MEM_WB_SLOT invalidated_slot = latch->zero;
        invalidated_slot.invalid = 1;
        return invalidated_slot;
    }
    else{
        return latch->slot[IN_LATCH];
    }
}