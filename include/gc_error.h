#ifndef _GC_MEMORY_ERROR_H_
#define _GC_MEMORY_ERROR_H_

#include "gc_utility.h"

// #define GC_LOG_SILENT

// Format uses 2 %s, 1: the severity decal. 2: the message
#define GC_FORMAT "[%s]\t%s"

#define GC_FORMAT_DEBUG "D"
#define GC_FORMAT_LOG "+"
#define GC_FORMAT_WARNING "W"
#define GC_FORMAT_ERROR "E"
#define GC_FORMAT_FATAL "-"

#define GC_COLOUR_RESET "\e[0m"

#define GC_COLOUR_DEBUG "\e[35"     // Purple
#define GC_COLOUR_LOG "\e[37"       // Gray
#define GC_COLOUR_WARNING "\e[33"   // Yellow
#define GC_COLOUR_ERROR "\e[0;31m"  // Red
#define GC_COLOUR_FATAL "\e[1;91m"  // Bold Intense Red


typedef int32_t (*gc_printCallback)(enum GC_SEVERITY severity, const char* restrict msg);
// Default format leaves newline to the user in case of non wanted behaviour in user callback
// without having to modify the base format
void gc_registerLogCallback(gc_printCallback callback);

int32_t gc_slog(enum GC_SEVERITY, const char* restrict msg, ...);
int32_t gc_debug(const char* restrict msg, ...);
int32_t gc_log(const char* restrict msg, ...);
int32_t gc_warning(const char* restrict msg, ...);
int32_t gc_error(const char* restrict msg, ...);
void    gc_fatal(const char* restrict msg, ...);


#endif /* _GC_MEMORY_GCERROR_H_ */
