//
// Created by user on 2024-06-18.
//

#include "cache_memory.h"
#include "../memory/memory.h"
#include "history_buffer.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

extern Memory memory;

extern uint32_t number_cache_read_hit;
extern uint32_t number_cache_read_miss;
extern uint32_t number_cache_write_hit;
extern uint32_t number_cache_write_miss;

#ifdef DIRECT_MAPPED_CACHE
Cache_memory cache;

uint32_t query_and_validate_cache(uint32_t tag, uint32_t index, uint32_t offset);
void load_cacheline(uint32_t address, uint32_t index, uint32_t tag);
uint32_t is_cache_full();
uint32_t check_flush_target();
uint32_t flush_cacheline(uint32_t index);

uint32_t do_cache_manipulation(uint32_t data, uint32_t address, uint32_t mem_write, uint32_t mem_read){
    uint32_t ret;
    uint32_t tag = (address >> 14);
    uint32_t index = (address >> 7) & 0x000007f;
    uint32_t offset = address & 0x7f;
    if(mem_read){
        printf("request tag : 0x%08x, cacheline tag : 0x%08x\n", tag, cache.cacheline[index].tag);
        if(query_and_validate_cache(tag, index, offset)){
            // cache hit case
            number_cache_read_hit++;
            ret = *(uint32_t*)(cache.cacheline[index].cacheline + offset);
            printf("CACHE HIT, return : %08x\n", ret);
        }
        else {
            // this function checks cache miss case
            number_cache_read_miss++;
            load_cacheline(address, index, tag);
            ret = *(uint32_t*)(cache.cacheline[index].cacheline + offset);
            printf("CACHE MISS, return : %08x\n", ret);
        }
        return ret;
    }
    else if(mem_write){
        printf("request tag : 0x%08x, cacheline tag : 0x%08x\n", tag, cache.cacheline[index].tag);
        if(query_and_validate_cache(tag, index, offset)){
            // cache hit case
            number_cache_write_hit++;
            cache.cacheline[index].dirty = 1;
            *(uint32_t*)(cache.cacheline[index].cacheline + offset) = data;
            printf("CACHE HIT, write data : %08x\n", data);
        }
        else {
            // this function checks cache miss case
            number_cache_write_miss++;
            load_cacheline(address, index, tag);
            cache.cacheline[index].dirty = 1;
            *(uint32_t*)(cache.cacheline[index].cacheline + offset) = data;
            printf("CACHE MISS, write data : %08x\n", data);
        }

        return 0;
    }
    return 0;
}

uint32_t query_and_validate_cache(uint32_t query_tag, uint32_t index, uint32_t offset){
    // index 접근 후, tag 동일 유무 판별
    uint32_t cacheline_tag = cache.cacheline[index].tag;
    if(cacheline_tag == query_tag && cache.cacheline[index].valid){
        return 1;
    }
    else{
        return 0;
    }
}

void load_cacheline(uint32_t address, uint32_t index, uint32_t tag){
    // check cold miss
    if(!(cache.cacheline[index].valid)){
        // nothing
    }
    else if(cache.cacheline[index].valid && tag != cache.cacheline[index].tag){
        // conflict miss
        printf("::CACHE FLUSH TRIGGER::\n");
        flush_cacheline(index);
    }

    uint32_t cacheline_head_address = (address) & 0xffffff80;
    cache.cacheline[index].tag = tag;
    cache.cacheline[index].valid = 1;
    memcpy(cache.cacheline[index].cacheline, &memory.mem[cacheline_head_address], 128);
}

uint32_t flush_cacheline(uint32_t index) {
    if (cache.cacheline[index].dirty) {
        // 메모리에 데이터를 푸시하는 연산이 필요함
        printf("::PUSH TO MEMORY::\n");

        // variable part
        uint32_t cacheline_address = (cache.cacheline[index].tag << 14) | (index << 7);
        memcpy(&memory.mem[cacheline_address], cache.cacheline[index].cacheline, 128);
    }
    cache.cacheline[index] = (Cacheline) {0};
    return index;
}


// useless for direct mapped cache
// no need to check capacity
uint32_t is_cache_full(){
    for(int i = 0; i < 128; i++){
        if(cache.cacheline[i].valid == 0){
            return 0;
        }
    }
    return 1;
}

uint32_t check_flush_target(){
    // selected algorith : Second Chance Algorithm
    // State machine work as extra life
    // if cache hit, then sca = 1
    // if capacity miss, then the sca of oldest one become 0 (give second chance) also check next oldest
    // if capacity miss again with no enable in sca, evict it
    // history buffer is needed as ring buffer
    return 0;
}

#endif

#ifdef FULLY_ASSOCIATED_CACHE

Cache_memory cache;
extern History_buffer history_buffer;

uint32_t query_and_validate_cache(uint32_t tag);
uint32_t load_cacheline(uint32_t address, uint32_t tag, uint32_t index);
uint32_t is_cache_full();
uint32_t evict_target_with_policy();
uint32_t flush_cacheline(uint32_t index);

uint32_t do_cache_manipulation(uint32_t data, uint32_t address, uint32_t isMemWrite, uint32_t isMemRead){
    uint32_t ret;
    uint32_t tag = (address >> 7);
    uint32_t offset = address & 0x7f;
    uint32_t access_index;

    access_index = query_and_validate_cache(tag);
    if(isMemRead){
        printf("%s_READ\t", ((int32_t)access_index >= 0 ?
                            "CACHE_HIT":
                      ((access_index == -1) ? "CAPACITY MISS": "COLD MISS")));
        if(access_index != -1 && access_index != -2){
            // cache hit case
            number_cache_read_hit++;
            cache.cacheline[access_index].policy = 1;
        }
        switch (access_index) {
            case -1:
                // 해당 단계에서, evict 결정 = history buffer 탐색
                access_index = evict_target_with_policy();
            case -2:
                number_cache_read_miss++;
                access_index = load_cacheline(address, tag, access_index);
                history_buffer_put(tag);
            default:
                ret = *(uint32_t*)(cache.cacheline[access_index].cacheline + offset);
                // set second chance

                break;
        }

        return ret;
    }
    else if(isMemWrite){
        printf("%s_WRITE\t", ((int32_t)access_index >= 0 ?
                        "CACHE_HIT":
                        ((access_index == -1) ? "CAPACITY MISS": "COLD MISS")));
        if(access_index != -1 && access_index != -2){
            // cache hit case
            number_cache_write_hit++;
            cache.cacheline[access_index].policy = 1;
        }
        switch (access_index) {
            case -1:
                access_index = evict_target_with_policy();
            case -2:
                number_cache_write_miss++;
                access_index = load_cacheline(address, tag, access_index);
                history_buffer_put(tag);
            default:
                // 캐시 메모리에 데이터를 작성하는거는 그냥 캐시라인 오프셋에 맞춰서 작성하는 방식으로 하는 것
                cache.cacheline[access_index].dirty = 1;
                *(uint32_t*)(cache.cacheline[access_index].cacheline + offset) = data;
                break;
        }
        // end of cache write operation
        return 0;
    }
    return 0;
}

uint32_t query_and_validate_cache(uint32_t query_tag){
    // index 접근 후, tag 동일 유무 판별
    // check cold miss & capacity miss
    // cold miss for -2;
    // capacity miss for -1;
    uint32_t ret = -1;
    uint32_t found_valid_zero = 0;
    for(int i = 0; i < 128; i++){
        if(cache.cacheline[i].valid == 0){
            found_valid_zero = 1;
        }
        if(cache.cacheline[i].tag == query_tag && cache.cacheline[i].valid){
            return i;
        }
    }

    if(found_valid_zero){
        ret = -2;
    }

    return ret;
}

uint32_t load_cacheline(uint32_t address, uint32_t tag, uint32_t index){
    // this function just load cacheline

    uint32_t ret_index;
    uint32_t cacheline_head_address = (address) & 0xffffff80;
    if(index == -2) {
        // cold miss
        ret_index = cache.available_tag_index++;
    }
    else{
        ret_index = index;
    }
    cache.cacheline[ret_index].valid = 1;
    cache.cacheline[ret_index].tag = tag;
    memcpy(cache.cacheline[ret_index].cacheline, &memory.mem[cacheline_head_address], 128);
    if(cache.available_tag_index >= 128){
        cache.available_tag_index = -1;
    }

    return ret_index;
}

uint32_t flush_cacheline(uint32_t index) {
    if (cache.cacheline[index].dirty) {
        // 메모리에 데이터를 푸시하는 연산이 필요함
        uint32_t cacheline_address = (cache.cacheline[index].tag << 7);
        memcpy(&memory.mem[cacheline_address], cache.cacheline[index].cacheline, 128);
    }
    cache.cacheline[index] = (Cacheline) {0};
    return index;
}


// useless for direct mapped cache
// no need to check capacity
uint32_t is_cache_full(){
    for(int i = 0; i < 128; i++){
        if(cache.cacheline[i].valid == 0){
            return 0;
        }
    }
    return 1;
}

uint32_t evict_target_with_policy(){
    // selected algorith : Second Chance Algorithm
    // State machine work as extra life
    // if cache hit, then sca = 1
    // if capacity miss, then the sca of oldest one become 0 (give second chance) also check next oldest
    // if capacity miss again with no enable in sca, evict it
    // history buffer is needed as ring buffer
    // history_buffer에 tag 정보를 넣고 비교하는 행위는 O(n * m)의 시간 복잡도를 가짐
    // 따라서, Random Access가 가능하도록, history buffer에는 tag가 아닌 index를 넣어서
    // 해당 캐쉬라인에 빠르게 접근할 수 있도록 한다.
    uint32_t oldest_index;
    while(1){
        oldest_index = history_buffer_peek_index();
        if(cache.cacheline[oldest_index].policy == 1) {
            cache.cacheline[oldest_index].policy = 0;
            uint32_t oldest_tag = history_buffer_get();
            history_buffer_put(oldest_tag);
        }
        else{
            flush_cacheline(oldest_index);
            break;
        }
    }

    return oldest_index;
}

void flush_all_cacheline(){
    for(int i = 0; i < CACHELINE_ENTRIES; i++){
        flush_cacheline(i);
    }
}
#endif
