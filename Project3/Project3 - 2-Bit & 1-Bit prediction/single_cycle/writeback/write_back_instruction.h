//
// Created by user on 2024-04-02.
//
#pragma once

#include "../../component/latch/latch.h"

#ifndef WRITE_BACK_INSTRUCTION
#define WRITE_BACK_INSTRUCTION
uint32_t write_back_pipe(MEM_WB_SLOT latch_out);
#endif