//
// Created by user on 2024-06-18.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef COMPUTER_ARCHITECTURE_CACHE_MEMORY_H
#define COMPUTER_ARCHITECTURE_CACHE_MEMORY_H

#define DIRECT_MAPPED_CACHE

#ifdef DIRECT_MAPPED_CACHE

/*
 *  Cache Store Size : 16KB
 *  Cache Line Size  : 128B
 *  Cache Line Entries : 2^18
 *  Tag Size : 18bit
 *  index Size : 7 bit
 *  Cacheline Offset : 7 bit
 */

#define CACHELINE_ENTRIES 128
#define CACHELINE_SIZE 0x80

typedef struct _cacheline{
    uint32_t tag;
    uint32_t policy;
    uint32_t valid;
    uint32_t dirty;
    uint8_t cacheline[CACHELINE_ENTRIES];
}Cacheline;

typedef struct _cache {
    Cacheline cacheline[CACHELINE_SIZE];
}Cache_memory;

uint32_t do_cache_manipulation(uint32_t data, uint32_t address, uint32_t mem_write, uint32_t mem_read);
#endif

#ifdef FULLY_ASSOCIATED_CACHE
#define FULLY_ASSOCIATED_CACHE

/*
 *  Cache Store Size : 16KB
 *  Cache line Size  : 128B
 *  Cacheline Entries : 128
 *  Tag Size : 25bit
 *  Cacheline Offset : 7bit
 *  NO INDEX
 */

#define CACHELINE_ENTRIES 128

typedef struct _cacheline{
    uint32_t tag;
    uint32_t policy;
    uint32_t valid;
    uint32_t dirty;
    uint8_t cacheline[128];
}Cacheline;

typedef struct _cache {
    Cacheline cacheline[0x80];
    uint32_t available_tag_index;
}Cache_memory;

uint32_t do_cache_manipulation(uint32_t data, uint32_t address, uint32_t mem_write, uint32_t mem_read);

#endif

#endif //COMPUTER_ARCHITECTURE_CACHE_MEMORY_H
