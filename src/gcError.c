#include "gcError.h"
#include "gcUtility.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static gcPrintCallback g_printCallback = 0;
static bool            g_useCallback   = false;

void gcRegisterLogCallback(gcPrintCallback callback)
{
    g_printCallback = callback;
    g_useCallback   = true;
}


const char* ParseMessage(enum GC_SEVERITY severity, const char* restrict msg, va_list args)
{
    // Parse Initial message
    size_t size    = vsnprintf(NULL, 0, msg, args) + 10;
    char*  userMsg = calloc(size, sizeof(char));
    if (userMsg == NULL)
        return NULL;
    vsnprintf(userMsg, size, msg, args);

    // Create format for output string
    const char* format         = NULL;
    const char* severityFormat = NULL;
    switch (severity)
    {
        case GC_SEVERITY_DEBUG:
            format         = GC_COLOUR_DEBUG GC_FORMAT GC_COLOUR_RESET;
            severityFormat = GC_FORMAT_DEBUG;
            break;
        case GC_SEVERITY_LOG:
            format         = GC_COLOUR_LOG GC_FORMAT GC_COLOUR_RESET;
            severityFormat = GC_FORMAT_LOG;
            break;
        case GC_SEVERITY_WARNING:
            format         = GC_COLOUR_WARNING GC_FORMAT GC_COLOUR_RESET;
            severityFormat = GC_FORMAT_WARNING;
            break;
        case GC_SEVERITY_ERROR:
            format         = GC_COLOUR_ERROR GC_FORMAT GC_COLOUR_RESET;
            severityFormat = GC_FORMAT_ERROR;
            break;

        default:
        case GC_SEVERITY_FATAL:
            format         = GC_COLOUR_FATAL GC_FORMAT GC_COLOUR_RESET;
            severityFormat = GC_FORMAT_FATAL;
            break;
    }
    if (format == NULL || severityFormat == NULL)
    {
        format         = "[%s](Both GC_FORMAT and GC_FORMAT_XXX has to be set)\t%s";
        severityFormat = "[FALLBACK]";
    }
    size      = snprintf(NULL, 0, format, severityFormat, userMsg) + 10;
    char* str = calloc(size, sizeof(char));
    if (!str)
        return NULL;

    snprintf(str, size, format, severityFormat, userMsg);
    free(userMsg);
    return str;
}


int32_t gcLogs(enum GC_SEVERITY severity, const char* restrict msg, ...)
{
#ifndef GC_LOG_SILENT
    if (severity < GC_SEVERITY_FATAL)
        gcWarning("Trying to format with severity %d, FATAL is %d. Message parsed as Fatal.",
                  severity,
                  GC_SEVERITY_FATAL);
#endif
    va_list args;
    va_start(args, msg);
    const char* parsedMsg = ParseMessage(severity, msg, args);
    va_end(args);

    if (parsedMsg == NULL)
        gcFatal("Unable to parse message %s", msg);

    int32_t ret = 0;
    if (g_useCallback)
        ret = g_printCallback(severity, parsedMsg);
    else
        ret = fprintf(stdout, "%s\n", parsedMsg);
    free((void*) parsedMsg);
    return ret;
}
int32_t gcDebug(const char* restrict msg, ...)
{
#ifdef _DEBUG
    va_list args;
    va_start(args, msg);
    const char* parsedMsg = ParseMessage(GC_SEVERITY_DEBUG, msg, args);
    va_end(args);

    if (parsedMsg == NULL)
        gcFatal("Unable to parse message %s", msg);

    int32_t ret = 0;
    if (g_useCallback)
        ret = g_printCallback(GC_SEVERITY_DEBUG, parsedMsg);
    else
        ret = fprintf(stdout, "%s\n", parsedMsg);
    free((void*) parsedMsg);
    return ret;
#endif
    return 0;
}
int32_t gcLog(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    const char* parsedMsg = ParseMessage(GC_SEVERITY_LOG, msg, args);
    va_end(args);

    if (parsedMsg == NULL)
        gcFatal("Unable to parse message %s", msg);

    int32_t ret = 0;
    if (g_useCallback)
        ret = g_printCallback(GC_SEVERITY_LOG, parsedMsg);
    else
        ret = fprintf(stdout, "%s\n", parsedMsg);
    free((void*) parsedMsg);
    return ret;
}
int32_t gcWarning(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    const char* parsedMsg = ParseMessage(GC_SEVERITY_WARNING, msg, args);
    va_end(args);

    if (parsedMsg == NULL)
        gcFatal("Unable to parse message %s", msg);

    int32_t ret = 0;
    if (g_useCallback)
        ret = g_printCallback(GC_SEVERITY_WARNING, parsedMsg);
    else
        ret = fprintf(stdout, "%s\n", parsedMsg);
    free((void*) parsedMsg);
    return ret;
}
int32_t gcError(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    const char* parsedMsg = ParseMessage(GC_SEVERITY_ERROR, msg, args);
    va_end(args);

    if (parsedMsg == NULL)
        gcFatal("Unable to parse message %s", msg);

    int32_t ret = 0;
    if (g_useCallback)
        ret = g_printCallback(GC_SEVERITY_ERROR, parsedMsg);
    else
        ret = fprintf(stdout, "%s\n", parsedMsg);
    free((void*) parsedMsg);
    return ret;
}
void gcFatal(const char* restrict msg, ...)
{
    va_list args;
    va_start(args, msg);
    const char* parsedMsg = ParseMessage(GC_SEVERITY_FATAL, msg, args);
    va_end(args);

    if (parsedMsg == NULL)
    {
        if (g_useCallback)
            g_printCallback(GC_SEVERITY_FATAL, msg);
        else
            fprintf(stderr, "ERROR: Unable to parse message %s", msg);
    }


    if (g_useCallback)
        g_printCallback(GC_SEVERITY_FATAL, parsedMsg);
    else
        fprintf(stdout, "%s\n", parsedMsg);
    free((void*) parsedMsg);
    exit(1);
}
