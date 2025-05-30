#ifndef _GC_MEMORY_ERROR_H_
#define _GC_MEMORY_ERROR_H_

#include "gcUtility.h"

// #define GC_LOG_SILENT

// Format uses 2 %s, 1: the severity decal. 2: the message
#define GC_FORMAT "[%s]\t%s"

#define GC_FORMAT_DEBUG "D"
#define GC_FORMAT_LOG "+"
#define GC_FORMAT_WARNING "W"
#define GC_FORMAT_ERROR "E"
#define GC_FORMAT_FATAL "-"

#define GC_COLOUR_RESET "\e[0m"

#define GC_COLOUR_DEBUG "\e[0;35m"    // Purple
#define GC_COLOUR_LOG "\e[0;37m"      // Gray
#define GC_COLOUR_WARNING "\e[0;33m"  // Yellow
#define GC_COLOUR_ERROR "\e[0;31m"    // Red
#define GC_COLOUR_FATAL "\e[1;91m"    // Bold Intense Red


typedef int32_t (*gcPrintCallback)(enum GC_SEVERITY severity, const char* restrict msg);
// Default format leaves newline to the user in case of non wanted behaviour in user callback
// without having to modify the base format
void gcRegisterLogCallback(gcPrintCallback callback);

int32_t gcLogs(enum GC_SEVERITY, const char* restrict msg, ...);
int32_t gcDebug(const char* restrict msg, ...);
int32_t gcLog(const char* restrict msg, ...);
int32_t gcWarning(const char* restrict msg, ...);
int32_t gcError(const char* restrict msg, ...);
void    gcFatal(const char* restrict msg, ...);


#endif /* _GC_MEMORY_GCERROR_H_ */
