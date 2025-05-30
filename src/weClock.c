#include "weClock.h"
#include "weUtility.h"

void weClockSetTime(we_clock_t* timer)
{
#if defined(_WIN32) || defined(__CYGWIN__)
    QueryPerformaceCounter(&timer->tick);
#elif defined(__unix__)
    clock_gettime(CLOCK_REALTIME, &timer->tick);
#endif
}

double weClockGetTime(we_clock_t* timer)
{
    double deltaTime = 0;

#if defined(_WIN32) || defined(__CYGWIN__)
    LARGE_INTEGER now = { 0 };
    QueryPerformaceCounter(&now);
    QueryPerformaceFrequency(&timer->frequency);

    deltaTime = (double) (now.QuadPart - timer->tick.QuadPart) / timer->frequency.QuadPart;
#elif defined(__unix__)
    struct timespec now = { 0 };
    clock_gettime(CLOCK_REALTIME, &now);

    deltaTime = (double) (now.tv_sec - timer->tick.tv_sec)
                + (now.tv_nsec - timer->tick.tv_nsec) / 1000000000.f;
#endif
    if (timer->limitHigh != 0 && timer->limitLow != 0)
        return wecl_clamp(deltaTime, timer->limitLow, timer->limitHigh);
    return deltaTime;
}

double weClockNow(void)
{
    double time = 0;
#if defined(_WIN32) || defined(__CYGWIN__)
    LARGE_INTEGER now, frequency = { 0 };
    QueryPerformaceCounter(&now);
    QueryPerformaceFrequency(&frequency);
    time = (double) now.QuadPart / timer->frequency.QuadPart;
#elif defined(__unix__)
    struct timespec now = { 0 };
    clock_gettime(CLOCK_REALTIME, &now);
    time = (double) (now.tv_sec) + (now.tv_nsec) / 1000000000.f;
#endif
    return time;
}
