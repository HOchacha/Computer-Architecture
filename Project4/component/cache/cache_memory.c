//
// Created by user on 2024-06-18.
//
#define FULLY_ASSOCIATED_CACHE
#include "cache_memory.h"
#include "../memory/memory.h"
#include <stdlib.h>
#include <memory.h>

extern Memory memory;

#ifdef DIRECT_MAPPED_CACHE
Cache_memory cache;

uint32_t query_and_validate_cache(uint32_t tag, uint32_t index, uint32_t offset);
void load_cacheline(uint32_t address, uint32_t index, uint32_t tag);
uint32_t is_cache_full();
uint32_t check_flush_target();
uint32_t flush_cacheline(uint32_t index, uint32_t tag);

uint32_t do_cache_manipulation(uint32_t data, uint32_t address, uint32_t isMemWrite, uint32_t isMemRead){
    uint32_t ret;
    uint32_t tag = (address >> 14);
    uint32_t index = (address >> 7) & 0x000007f;
    uint32_t offset = address & 0x7f;
    if(isMemRead){

        if(query_and_validate_cache(tag, index, offset)){
            // cache hit case
            ret = cache.cacheline[index].cacheline[offset];

            // no need to implement sca
            cache.cacheline[index].policy = 1;
        }
        else {
            // this function checks cache miss case
            load_cacheline(address, index, tag);
            ret = cache.cacheline[index].cacheline[offset];
        }
        return ret;
    }
    else if(isMemWrite){
        // 캐시 메모리에 데이터를 작성하는거는 그냥 캐시라인 오프셋에 맞춰서 작성하는 방식으로 하는 것
        cache.cacheline[index].dirty = 1;
        cache.cacheline[index].cacheline[offset] = data;
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
        flush_cacheline(index, tag);
    }

    uint32_t cacheline_head_address = (address) & 0xffffff80;
    cache.cacheline[index].tag = tag;
    cache.cacheline[index].valid = 1;
    memcpy(cache.cacheline[index].cacheline, &memory.mem[cacheline_head_address], 128);
}

uint32_t flush_cacheline(uint32_t index, uint32_t tag) {
    if (cache.cacheline[index].dirty) {
        // 메모리에 데이터를 푸시하는 연산이 필요함
        uint32_t cacheline_address = (tag << 14) | (index << 7);
        memcpy(&memory.mem[cacheline_address], cache.cacheline[index].cacheline, 128);
    }
    cache.cacheline[index] = (Cacheline) {0};
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

uint32_t query_and_validate_cache(uint32_t tag, uint32_t offset);
uint32_t load_cacheline(uint32_t address, uint32_t tag);
uint32_t is_cache_full();
uint32_t check_evict_target();
uint32_t flush_cacheline(uint32_t index, uint32_t tag);

uint32_t do_cache_manipulation(uint32_t data, uint32_t address, uint32_t isMemWrite, uint32_t isMemRead){
    uint32_t ret;
    uint32_t tag = (address >> 7);
    uint32_t offset = address & 0x7f;
    uint32_t access_index;

    access_index = query_and_validate_cache(tag, offset);
    if(isMemRead){

        switch (access_index) {
            case -1:
                flush_cacheline();
            case -2:
                load_cacheline(address, tag);
            default:
                ret = cache.cacheline[access_index].cacheline[offset];
                // set second chance
                cache.cacheline[access_index].policy = 1;
                break;
        }

        return ret;
    }
    else if(isMemWrite){

        switch (access_index) {
            case -1:
                flush_cacheline();
            case -2:
                load_cacheline(address, tag);
            default:
                ret = cache.cacheline[access_index].cacheline[offset];
                // set second chance
                cache.cacheline[access_index].policy = 1;
                break;
        }

        // 캐시 메모리에 데이터를 작성하는거는 그냥 캐시라인 오프셋에 맞춰서 작성하는 방식으로 하는 것
        cache.cacheline[access_index].dirty = 1;
        cache.cacheline[access_index].cacheline[offset] = data;
        return 0;
    }
    return 0;
}

uint32_t query_and_validate_cache(uint32_t query_tag, uint32_t offset){
    // index 접근 후, tag 동일 유무 판별
    // check cold miss & capacity miss
    // cold miss for -2;
    // capacity miss for -1;
    uint32_t ret = -1;
    for(int i = 0; i < 128; i++){
        if(cache.cacheline[i].valid == 0){
            ret = -2;
        }
        if(cache.cacheline[i].tag == query_tag){
            return i;
        }
    }
    return ret;
}

uint32_t load_cacheline(uint32_t address, uint32_t tag){
    // check cold miss
    uint32_t ret_index;

    if(cache.available_tag_index != -1){
        // capacity miss
        check_evict_target();
    }
    else{
        // cold miss
        uint32_t cacheline_head_address = (address) & 0xffffff80;
        ret_index = cache.available_tag_index;
        memcpy(cache.cacheline[cache.available_tag_index].cacheline, &memory.mem[cacheline_head_address], 128);
        if(cache.available_tag_index >= 128){
            cache.available_tag_index = -1;
        }
    }

    return ret_index;
}

uint32_t flush_cacheline(uint32_t index, uint32_t tag) {
    if (cache.cacheline[index].dirty) {
        // 메모리에 데이터를 푸시하는 연산이 필요함
        uint32_t cacheline_address = (tag << 14) | (index << 7);
        memcpy(&memory.mem[cacheline_address], cache.cacheline[index].cacheline, 128);
    }
    cache.cacheline[index] = (Cacheline) {0};
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

uint32_t check_evict_target(){
    // selected algorith : Second Chance Algorithm
    // State machine work as extra life
    // if cache hit, then sca = 1
    // if capacity miss, then the sca of oldest one become 0 (give second chance) also check next oldest
    // if capacity miss again with no enable in sca, evict it
    // history buffer is needed as ring buffer
    return 0;
}


#endif