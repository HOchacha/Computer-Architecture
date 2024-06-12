#pragma once

#include "../../component/latch/latch.h"
#include "../../component/last_branch_prediction/last_branch_predictor.h"

#ifndef EXECUTE_INSTRUCTION
#define EXECUTE_INSTRUCTION
EX_MEM_SLOT execute_instruction_pipe(ID_EX_SLOT id_ex_latch_out,
                                     EX_MEM_SLOT ex_mem_slot,
                                     MEM_WB_SLOT mem_wb_slot,
                                     IF_ID_LATCH* if_id_latch,
                                     ID_EX_LATCH* id_ex_latch,
                                     uint32_t* TERMINATION,
                                     branch_target_buffer* btb);
#endif