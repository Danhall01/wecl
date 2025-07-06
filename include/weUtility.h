#ifndef _WECL_UTILITY_H_
#define _WECL_UTILITY_H_

#include <stdint.h>

#define _WECL_MACRO_VAR_CONCAT(prefix, suffix) prefix##suffix
#define _WECL_MACRO_VAR_EXPAND(prefix, suffix) _WECL_MACRO_VAR_CONCAT(prefix, suffix)
// Define a variable inside of a macro
#define WECL_MACRO_VAR(name) _WECL_MACRO_VAR_EXPAND(name, __LINE__)

// Clamps value between min and max, all typees has to be castable between eachother
#define wecl_clamp(value, min, max) (value > max ? max : (value < min ? min : value))

// Severity level of gc functions in increasing order, 0 is debug, highest is fatal error
enum WECL_SEVERITY : uint8_t
{
    WECL_SEVERITY_DEBUG = 0,
    WECL_SEVERITY_TRACE,
    WECL_SEVERITY_LOG,
    WECL_SEVERITY_INFO,
    WECL_SEVERITY_WARNING,
    WECL_SEVERITY_ERROR,
    WECL_SEVERITY_FATAL,
};

// Executes the 'before' function before the scope and the 'after' function after the scope (For
// conditional scope use gc_defer_cond)
#define wecl_defer(before, after)                                                                  \
    for (int32_t WECL_MACRO_VAR(_i) = (before, 0); !WECL_MACRO_VAR(_i);                            \
         WECL_MACRO_VAR(_i)         = (after, WECL_MACRO_VAR(_i) + 1))


// Executes the functions in their respective places, 'after' and scope is only called if condition
// is fullfilled
// @ requires before to return a castable int32_t value AND cond to be an int32_t castable value
#define wecl_defer_cond(before, cond, after)                                                       \
    for (int32_t WECL_MACRO_VAR(_i) = (int32_t) before; WECL_MACRO_VAR(_i) == cond;                \
         WECL_MACRO_VAR(_i)         = (after, !cond))


// Executes the functions in their respective places, 'after' and scope is only called if condition
// is not fullfilled
// @ requires before to return a castable int32_t value AND cond to be an int32_t castable value
#define wecl_defer_ncond(before, cond, after)                                                      \
    for (int32_t WECL_MACRO_VAR(_i) = (int32_t) before; WECL_MACRO_VAR(_i) != cond;                \
         WECL_MACRO_VAR(_i)         = (after, cond))

// Executes the assigned function after the scope has finished running
#define wecl_scope(after)                                                                          \
    for (int32_t WECL_MACRO_VAR(_i) = 0; !WECL_MACRO_VAR(_i); WECL_MACRO_VAR(_i) = (after, 1))


#endif /* _WECL_UTILITY_H_ */
