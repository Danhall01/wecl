#include <stdio.h>

#define CLR_GREEN "\e[0;32m"
#define CLR_RED "\e[0;31m"
#define CLR_CLEAR "\e[0m"

extern bool TestError(void);
extern bool TestUtility(void);
extern bool TestClock(void);

int main(void)
{
    printf(CLR_GREEN "Starting Tests...\n" CLR_CLEAR);

    bool success = false;

    do
    {
        if (!TestError())
            break;
        if (!TestUtility())
            break;
        if (!TestClock())
            break;

        success = true;
    } while (false);

    if (!success)
        return printf(CLR_RED "Tests failed (See log above for information)\n" CLR_CLEAR), 1;
    printf(CLR_GREEN "Tests Done!\n" CLR_CLEAR);
    return 0;
}
