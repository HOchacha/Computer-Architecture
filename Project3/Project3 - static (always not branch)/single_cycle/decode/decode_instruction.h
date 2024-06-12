#pragma once
#include <stdint.h>

#include <stdio.h>
#include "../../component/latch/latch.h"
#include "../../component/miscelenous/decode_type.h"

#ifndef DECODED_INSTRUCTION
#define DECODED_INSTRUCTION


void print_instruction_info(Decoded_values v);
uint32_t sign_extend_16_to_32(uint16_t input_data);
Decoded_values decode_instruction(uint32_t);


#endif

