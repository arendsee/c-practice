/* valgrind will find the leaked byte. Setting the --show-leak option
 * (--show-leak=full or --show-leak=symary) will trace the leak to its function
 * of origin.
 * */

#include <stdlib.h>
#include <stdio.h>

void leak_one_byte(){
    char * c = malloc(sizeof(char));
}

int main(){
    leak_one_byte();
    return 0;
}
