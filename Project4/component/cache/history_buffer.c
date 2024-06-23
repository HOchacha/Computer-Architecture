//
// Created by user on 2024-06-20.
//

#include <stdlib.h>
#include "history_buffer.h"
History_buffer history_buffer;

History_buffer history_buffer = {
        .head = 0,
        .tail = 0,
        .max = 128, // 초기화
        .is_full = 0
};

uint32_t history_buffer_is_empty(){
    return (history_buffer.head
            == history_buffer.tail && !history_buffer.is_full);
}

uint32_t history_buffer_is_full(){
    return (history_buffer.is_full);
}

void history_buffer_put(uint32_t item){
    history_buffer.buffer[history_buffer.head] = item;
    if(history_buffer.is_full){
        history_buffer.tail = (history_buffer.tail + 1) % history_buffer.max;
    }
    history_buffer.head = (history_buffer.head + 1) % history_buffer.max;
    history_buffer.is_full = (history_buffer.head == history_buffer.tail);
}

uint32_t history_buffer_get(){
    if(history_buffer_is_empty()){
        return -1;
    }
    uint32_t item = history_buffer.buffer[history_buffer.tail];
    history_buffer.tail = (history_buffer.tail + 1) % history_buffer.max;
    history_buffer.is_full = 0;

    return item;
}

// peek은 인덱스의 최후방 값을 반환한다.
uint32_t history_buffer_peek() {
    if(history_buffer_is_empty()) {
        return -1; // 오류: 버퍼가 비어 있음
    }
    return history_buffer.buffer[history_buffer.tail];
}

uint32_t history_buffer_peek_index(){
    if(history_buffer_is_empty()){
        return -1;
    }
    return history_buffer.tail;
}