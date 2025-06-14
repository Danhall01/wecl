#ifndef _INCLUDE_WEMEMORY_H_
#define _INCLUDE_WEMEMORY_H_

#include "stdint.h"
#include <stddef.h>

void  weDefaultFree(void* ptr);
void* weDefaultAlloc(size_t size);
void* weDefaultCalloc(size_t size);

#if !__has_attribute(cleanup)
#error "The `cleanup` attribute is not supported with current compiler."
#endif  // __has_attribute(cleanup)


// Decalare variable which has a destructor called at the end of the scope
#define wecl_raii(type, name, destructor) type __attribute__((cleanup(destructor))) name

#define wecl_araii(name, destructor) auto __attribute__((cleanup(destructor))) name

// Decalre and allocate memory. Memory is freed at the end of the scope
#define wecl_ralloc(type, name, amount, alloc, free)                                               \
    type __attribute__((cleanup(free))) name = alloc(sizeof(*name) * amount)


// Declare and allocate memory from the weDefaultAlloc function, memory is automatically freed at
// the end of the scope
#define wecl_rmalloc(type, name, amount)                                                           \
    type __attribute__((cleanup(weDefaultFree))) name = weDefaultAlloc(sizeof(*name) * amount)


// Declare and allocate memory from the weDefaultCalloc function, memory is automatically freed at
// the end of the scope
#define wecl_rcalloc(type, name, amount)                                                           \
    type __attribute__((cleanup(weDefaultFree))) name = weDefaultCalloc(sizeof(*name) * amount)


#endif /* _INCLUDE_WEMEMORY_H_ */
