//
// Created by user on 2024-05-31.
//

#ifndef COMPUTER_ARCHITECTURE_LAST_BRANCH_PREDICTOR_H
#define COMPUTER_ARCHITECTURE_LAST_BRANCH_PREDICTOR_H

#define SLOT_SIZE 10

#include <stdint.h>


typedef struct _branch_target_buffer_slot{
    uint32_t branch_inst_addr;
    uint32_t is_branch; // this field has 32 bits, but work as 1bit.
    uint32_t branch_target_addr;
}BTB_slot;

typedef struct _branch_target_buffer{
    uint32_t head;
    uint32_t tail;
    BTB_slot slot[SLOT_SIZE];
}branch_target_buffer;

typedef struct _branch_prediction{
    uint32_t target_address;
    uint32_t is_branch_predicted;
    uint32_t BTB_index;
}branch_prediction;

typedef struct _branch_correction{
    uint32_t is_mis_prediction;
    uint32_t revised_addr;
}branch_correction;

branch_prediction get_prediction(branch_target_buffer* btb, uint32_t current_pc);
branch_correction update_history_and_status(uint32_t btb_index,
                                            branch_target_buffer* btb,
                                            uint32_t ex_is_branch,
                                            uint32_t current_pc,
                                            uint32_t branch_addr);
#endif //COMPUTER_ARCHITECTURE_LAST_BRANCH_PREDICTOR_H
