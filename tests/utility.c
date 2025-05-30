#include "weUtility.h"
#include <stdio.h>

static int32_t foo(void)
{
    printf("Foo with 12\n");
    return 12;
}


bool TestUtility(void)
{
    printf("==========\nTesting weUtility..\n");

    wecl_defer(printf("before\n"), printf("after\n")) { printf("Inside of block\n"); }


    wecl_defer_cond(foo(), 12, printf("After was called from foo with cond 12\n"))
    {
        printf("Inside block from foo 12 cond\n");
    }

    wecl_defer_ncond(foo(), 12, printf(("After foo 12 ncond (SHOULD NOT BE CALLED)\n")))
    {
        printf("Inside of ncond block, SHOULD NOT BE CALLED\n");
    }


    wecl_scope(printf("After wecl_scope\n")) { printf("wecl_scope block\n"); }


    printf("weUtility passed all tests\n==========\n");
    return true;
}
