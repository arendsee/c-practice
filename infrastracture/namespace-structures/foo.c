#include <stdio.h>

#include "foo.h"

static int my_bar(int a, int b) {
    return a - b;
}

static void my_baz(void) {
    printf("foo-baz\n");
}

namespace_struct const foo = { .bar = my_bar, .baz = my_baz };
