#ifndef _INCLUDE_WEMEMORY_H_
#define _INCLUDE_WEMEMORY_H_

#include "stdint.h"
#include <stddef.h>

void  weDefaultFree(void* ptr);
void* weDefaultAlloc(size_t size);
void* weDefaultCalloc(size_t size);

#if !__has_attribute(cleanup)
#error "The `cleanup` attribute is not supported with current compiler."
#else


#define wecl_raii __attribute__((cleanup(weDefaultFree)))
#define wecl_raiiA(...) __attribute__((cleanup(__VA_ARGS__)))


#endif  // __has_attribute(cleanup)
#endif  /* _INCLUDE_WEMEMORY_H_ */
