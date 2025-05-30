#ifndef _WECL_ALLOCATORS_H_
#define _WECL_ALLOCATORS_H_


#include <stdint.h>

typedef struct
{
    void* begin;
    void* end;
} we_arena_t;


void* we_allocArena_helper(we_arena_t* arena, int64_t size, int32_t align, int32_t count);

#define we_allocArena(arena, type, size) (type*)


#endif /* _WECL_ALLOCATORS_H_ */
