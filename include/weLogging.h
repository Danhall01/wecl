#ifndef _WECL_MEMORY_ERROR_H_
#define _WECL_MEMORY_ERROR_H_

#include "weUtility.h"

// TODO: Have a fallback static memory block in case of malloc error
// TODO: Frametrace and trace should be different severity levels
// TODO: Frametrace should only dump to file at the end of the program

// #define GC_LOG_SILENT

// Format uses 2 %s, 1: the severity decal. 2: the message
#define WECL_FORMAT "[%s]\t%s"

#define WECL_FORMAT_DEBUG "D"
#define WECL_FORMAT_LOG "+"
#define WECL_FORMAT_INFO "ⓘ"
#define WECL_FORMAT_TRACE "T"
#define WECL_FORMAT_WARNING "W"
#define WECL_FORMAT_ERROR "E"
#define WECL_FORMAT_FATAL "-"

#define WECL_COLOUR_RESET "\e[0m"

#define WECL_COLOUR_DEBUG "\e[0;35m"    // Purple
#define WECL_COLOUR_TRACE "\e[0;37m"    // White
#define WECL_COLOUR_LOG "\e[0;32m"      // Green
#define WECL_COLOUR_INFO "\e[0;37m"     // Gray
#define WECL_COLOUR_WARNING "\e[0;33m"  // Yellow
#define WECL_COLOUR_ERROR "\e[0;31m"    // Red
#define WECL_COLOUR_FATAL "\e[1;91m"    // Bold Intense Red


typedef int32_t (*wePrintCallback)(enum WECL_SEVERITY severity, const char* restrict msg);
// Default format leaves newline to the user in case of non wanted behaviour in user callback
// without having to modify the base format
void weRegisterLogCallback(wePrintCallback callback);

int32_t wePrintl(enum WECL_SEVERITY, const char* restrict msg, ...);
int32_t weDebug(const char* restrict msg, ...);
int32_t weLog(const char* restrict msg, ...);
int32_t weInfo(const char* restrict msg, ...);
int32_t weWarning(const char* restrict msg, ...);
int32_t weError(const char* restrict msg, ...);
void    weFatal(const char* restrict msg, ...);

// Trace system, writes to file
// Sets the starting point of current trace buffer
void weNewTraceFrame();
// Sends a trace message to be parsed by the frame buffer, upon crash these messages will be saved
// to file
int32_t weTrace(const char* restrict msg, ...);

#endif /* _WECL_MEMORY_GCERROR_H_ */
