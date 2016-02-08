#include <stdio.h>
#include "foo.h"
#include "goo.h"

int main(void) {
    printf("foo says: ");
    foo.baz();
    printf("goo says: ");
    goo.baz();
    printf("foo->%d goo->%d\n", foo.bar(3, 4), goo.bar(3, 4));
    return 0;
}
