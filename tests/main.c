#include <stdio.h>

extern void TestUtility(void);

int main(void)
{
    printf("Starting Tests...\n");

    TestUtility();

    printf("Tests Done!\n");
    return 0;
}
