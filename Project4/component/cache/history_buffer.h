//
// Created by user on 2024-06-20.
//
#include <stdint.h>
#ifndef COMPUTER_ARCHITECTURE_HISTORY_BUFFER_H
#define COMPUTER_ARCHITECTURE_HISTORY_BUFFER_H

// working as a ring buffer
typedef struct _history_buffer{
    uint32_t buffer[128];
    uint32_t head;
    uint32_t tail;
    uint32_t max;
    uint32_t is_full;
}History_buffer;
uint32_t history_buffer_is_empty();
uint32_t history_buffer_is_full();
void history_buffer_put(uint32_t item);
uint32_t history_buffer_get();
uint32_t history_buffer_peek();
uint32_t history_buffer_peek_index();
#endif //COMPUTER_ARCHITECTURE_HISTORY_BUFFER_H
