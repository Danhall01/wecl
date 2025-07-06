#include "weLogging.h"
#include "weUtility.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static wePrintCallback g_printCallback = nullptr;

void weRegisterLogCallback(wePrintCallback callback) { g_printCallback = callback; }


const char* ParseMessage(enum WECL_SEVERITY severity, const char* restrict msg, va_list args)
{
    // Parse Initial message
    // vsnprintf CONSUMES the va_list when used, thus we need to create a copy to get the size
    va_list sizeargs;
    va_copy(sizeargs, args);
    size_t size = vsnprintf(NULL, 0, msg, sizeargs) + 1;
    va_end(sizeargs);
    char* userMsg = calloc(size, sizeof(char));
    if (userMsg == NULL)
        return NULL;
    vsnprintf(userMsg, size, msg, args);

    // Create format for output string
    const char* format         = NULL;
    const char* severityFormat = NULL;
    switch (severity)
    {
        case WECL_SEVERITY_DEBUG:
            format         = WECL_COLOUR_DEBUG WECL_FORMAT WECL_COLOUR_RESET;
            severityFormat = WECL_FORMAT_DEBUG;
            break;
        case WECL_SEVERITY_LOG:
            format         = WECL_COLOUR_LOG WECL_FORMAT WECL_COLOUR_RESET;
            severityFormat = WECL_FORMAT_LOG;
            break;
        case WECL_SEVERITY_INFO:
            format         = WECL_COLOUR_INFO WECL_FORMAT WECL_COLOUR_RESET;
            severityFormat = WECL_FORMAT_INFO;
            break;
        case WECL_SEVERITY_TRACE:
            format         = WECL_COLOUR_TRACE WECL_FORMAT WECL_COLOUR_RESET;
            severityFormat = WECL_FORMAT_TRACE;
            break;
        case WECL_SEVERITY_WARNING:
            format         = WECL_COLOUR_WARNING WECL_FORMAT WECL_COLOUR_RESET;
            severityFormat = WECL_FORMAT_WARNING;
            break;
        case WECL_SEVERITY_ERROR:
            format         = WECL_COLOUR_ERROR WECL_FORMAT WECL_COLOUR_RESET;
            severityFormat = WECL_FORMAT_ERROR;
            break;

        default:
        case WECL_SEVERITY_FATAL:
            format         = WECL_COLOUR_FATAL WECL_FORMAT WECL_COLOUR_RESET;
            severityFormat = WECL_FORMAT_FATAL;
            break;
    }
    if (format == NULL || severityFormat == NULL)
    {
        format         = "[%s](Both WECL_FORMAT and WECL_FORMAT_XXX has to be set)\t%s";
        severityFormat = "[FALLBACK]";
    }
    size      = snprintf(NULL, 0, format, severityFormat, userMsg) + 1;
    char* str = calloc(size, sizeof(char));
    if (!str)
        return NULL;

    snprintf(str, size, format, severityFormat, userMsg);
    free(userMsg);
    return str;
}

static int32_t InternalPrint(enum WECL_SEVERITY severity, const char* msg, va_list args)
{
    const char* parsedMsg = ParseMessage(severity, msg, args);

    if (parsedMsg == NULL)
        weFatal("Unable to parse message %s", msg);

    int32_t ret = 0;
    if (g_printCallback != nullptr)
        ret = g_printCallback(severity, parsedMsg);
    else
    {
        ret = fprintf(stdout, "%s\n", parsedMsg);
        if (severity >= WECL_SEVERITY_FATAL)
            exit(1);
    }
    free((void*) parsedMsg);
    return ret;
}


int32_t wePrintl(enum WECL_SEVERITY severity, const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    int32_t ret = InternalPrint(severity, msg, args);
    va_end(args);
    return ret;
}
int32_t weDebug(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    int32_t ret = InternalPrint(WECL_SEVERITY_DEBUG, msg, args);
    va_end(args);
    return ret;
}
int32_t weLog(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    int32_t ret = InternalPrint(WECL_SEVERITY_LOG, msg, args);
    va_end(args);
    return ret;
}
int32_t weInfo(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    int32_t ret = InternalPrint(WECL_SEVERITY_INFO, msg, args);
    va_end(args);
    return ret;
}
int32_t weWarning(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    int32_t ret = InternalPrint(WECL_SEVERITY_WARNING, msg, args);
    va_end(args);
    return ret;
}
int32_t weError(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    int32_t ret = InternalPrint(WECL_SEVERITY_ERROR, msg, args);
    va_end(args);
    return ret;
}
void weFatal(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    InternalPrint(WECL_SEVERITY_FATAL, msg, args);
    va_end(args);
    exit(1);
}


static FILE* g_tracebuffer;
void         weNewTraceFrame()
{
    const char* fname = ".trace_output.txt";
    if (!g_tracebuffer)
        g_tracebuffer = fopen(fname, "a");
    freopen(fname, "w", g_tracebuffer);
    freopen(fname, "a", g_tracebuffer);
}
int32_t weTrace(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    const char* parsedMsg = ParseMessage(WECL_SEVERITY_TRACE, msg, args);
    va_end(args);

    if (parsedMsg == NULL)
        weFatal("Unable to parse message %s", msg);

    int32_t ret = fprintf(g_tracebuffer, "%s\n", msg);
    free((void*) parsedMsg);
    return ret;
}
