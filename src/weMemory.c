#include "weMemory.h"

#include <stdlib.h>

void weDefaultFree(void* ptr)
{
    void** p = (void**) ptr;
    free(*p);
}
void* weDefaultAlloc(size_t size) { return malloc(size); }
void* weDefaultCalloc(size_t size) { return calloc(size, 1); }
