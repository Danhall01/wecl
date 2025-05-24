#ifndef _GC_UTILITY_H_
#define _GC_UTILITY_H_

#include <stdint.h>
#define GC_MACRO_VAR(name)

#define clamp(value, min, max) (value > max ? max : (value < min ? min : value));


// Executes the 'before' function before the scope and the 'after' function after the scope (For
// conditional scope use gc_defer_cond)
#define gc_defer(before, after)                                                                    \
    for (int32_t GC_MACRO_VAR(_i) = (before, 0); !GC_MACRO_VAR(_i);                                \
         GC_MACRO_VAR(_i)         = (after, GC_MACRO_VAR(_i) + 1))


// Executes the functions in their respective places, 'after' and scope is only called if condition
// is fullfilled
#define gc_defer_cond(before, cond, after)                                                         \
    for (int32_t GC_MACRO_VAR(_i) = before; GC_MACRO_VAR(_i) == cond;                              \
         GC_MACRO_VAR(_i)         = (after, !cond))


// Executes the functions in their respective places, 'after' and scope is only called if condition
// is not fullfilled
#define gc_defer_ncond(before, cond, after)                                                        \
    for (int32_t GC_MACRO_VAR(_i) = before; GC_MACRO_VAR(_i) != cond;                              \
         GC_MACRO_VAR(_i)         = (after, cond))

// Executes the assigned function after the scope has finished running
#define gc_scope(after)


#endif /* _GC_MACROS_BUILDER_H_ */
