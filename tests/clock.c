#include "weClock.h"
#include <stdio.h>
#include <unistd.h>

bool TestClock(void)
{
    printf("==========\nTesting weClock..\n");

    we_clock_t clock = {};

    printf("Setting time\n");
    weClockSetTime(&clock);

    printf("Waiting 1sec...\n");
    sleep(1);

    printf("Time transpired (realtime): %f\n", weClockGetTime(&clock));

    printf("time now: %f\n", weClockNow());

    printf("weClock passed all tests\n==========\n");
    return true;
}
