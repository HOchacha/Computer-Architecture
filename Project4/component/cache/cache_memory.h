//
// Created by user on 2024-06-18.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef COMPUTER_ARCHITECTURE_CACHE_MEMORY_H
#define COMPUTER_ARCHITECTURE_CACHE_MEMORY_H


#ifdef DIRECT_MAPPED_CACHE

/*
 *  Cache Store Size : 16KB
 *  Cache Line Size  : 128B
 *  Cache Line Entries : 2^18
 *  Tag Size : 18bit
 *  index Size : 7 bit
 *  Cacheline Offset : 7 bit
 */

typedef struct _cacheline{
    uint32_t tag;
    uint32_t policy;
    uint32_t valid;
    uint32_t dirty;
    uint8_t cacheline[128];
}Cacheline;

typedef struct _cache {
    Cacheline cacheline[0x80];
}Cache_memory;

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

#endif


#ifdef SET_ASSOCIATIVE_CACHE_2WAY
#define SET_ASSOCIATIVE_CACHE_2WAY

/*
 *  Cache Store Size : 16KB
 *  Cache line Size  : 128B
 *  Cacheline Entries : 128
 *  Tag Size : 26bit
 *  Cacheline Offset : 7bit
 *  for 2way index : 6bit
 */

typedef struct _cacheline{
    uint32_t cacheline[128];
}Cacheline;

typedef struct _cache{
    uint32_t tag;
    uint32_t policy;
    uint32_t valid;
    uint32_t dirty;
    Cacheline cacheline[0x40];
};


#endif

#ifdef SET_ASSOCIATIVE_CACHE_4WAY
#define SET_ASSOCIATIVE_CACHE_4WAY

/*
 *  Cache Store Size : 16KB
 *  Cache line Size  : 128B
 *  Cacheline Entries : 128
 *  Tag Size : 26bit
 *  Cacheline Offset : 7bit
 *  for 2way index : 6bit
 */

typedef struct _cacheline{
    uint32_t cacheline[128];
}Cacheline;

typedef struct _cache{
    uint32_t tag;
    uint32_t policy;
    uint32_t valid;
    uint32_t dirty;
    Cacheline cacheline[0x20];
};
#endif

#endif //COMPUTER_ARCHITECTURE_CACHE_MEMORY_H
