#ifndef _GC_MEMORY_ALLOCATORS_H_
#define _GC_MEMORY_ALLOCATORS_H_


#include <stdint.h>

typedef struct
{
    void* begin;
    void* end;
} gc_arena_t;


void* gc_allocArena_helper(gc_arena_t* arena, int64_t size, int32_t align, int32_t count);

#define gc_allocArena(arena, type, size) (type*)


#endif /* _GC_MEMORY_ALLOCATORS_H_ */
