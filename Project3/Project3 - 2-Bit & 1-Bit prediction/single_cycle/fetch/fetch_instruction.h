#pragma once

#include <stdint.h>
#include "../../component/latch/latch.h"
#include "../../component/last_branch_prediction/last_branch_predictor.h"

#ifndef FETCH_INSTRUCTION
#define FETCH_INSTRUCTION
//PC의 경우, Architectural State이므로 전역 변수로 접근하도록 한다.
uint32_t fetch_instruction(uint32_t PC);

IF_ID_SLOT fetch_instruction_pipe(uint32_t pc, uint32_t termination, branch_target_buffer* btb);
#endif