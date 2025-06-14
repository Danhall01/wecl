#include "weLogging.h"
#include "weUtility.h"
#include <stdint.h>
#include <stdio.h>

int32_t echo(enum WECL_SEVERITY severity, const char* msg)
{
    printf("%s\n", msg);
    return 0;
}
int32_t empty(enum WECL_SEVERITY severity, const char* msg) { return 0; }
bool    TestError(void)
{
    printf("==========\nTesting weError..\n");

    printf("\n== Testing with default pipe\n");
    weDebug("dbg with num 5 | %d", 5);
    weLog("formatted: %s", "Log message");
    weWarning("Warn message with double 5.0 %f", 5.0);
    weError("Error message with floating point 5.f %f", 5.f);

    printf("\n== Testing callback pipe\n");
    weRegisterLogCallback(echo);
    weDebug("Debug msg, number 10 | %d", 10);
    weLog("Log msg, double 10.0 | %f", 10.0);
    weWarning("Warning msg, floating point 10.f | %f", 10.f);
    weError("Error msg, formatted str: %s", "formatted str");


    printf("\n== Testing empty pipe and reset (Should be 1 message)\n");
    weRegisterLogCallback(empty);
    weLog("Should not be  shown");

    weRegisterLogCallback(NULL);
    wePrintl(WECL_SEVERITY_ERROR, "This should be shown");

    if (false)
        weFatal(("Testing for linker errors"));


    printf("== Testing frame trace, writing the same message 10x, file should include only 1\n");
    int32_t i = 0;
    while (i < 10)
    {
        weNewTraceFrame();
        weTrace("Temporary trace message.");
        ++i;
    }

    printf("weError passed all tests\n==========\n");
    return true;
}
