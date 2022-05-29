#include<criterion/criterion.h>
#include <criterion/new/assert.h>
#include<string.h>

void setup(void)
{
    puts("Runs before the test");
}

void teardown(void)
{
    puts("Runs after the test");
}

Test(simple3, test, .init = setup, .fini = teardown){
    cr_assert(eq(str, "hhello", "hello"));
}
