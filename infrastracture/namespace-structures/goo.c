#include <stdio.h>

#include "goo.h"

static int my_bar(int a, int b) {
    return a + b;
}

static void my_baz(void) {
    printf("goo-baz\n");
}

namespace_struct const goo = { .bar = my_bar, .baz = my_baz };
