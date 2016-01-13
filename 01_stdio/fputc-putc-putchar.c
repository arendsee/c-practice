#include <stdio.h>
#include <string.h>

int main(){
    FILE * f = fopen("delete-me.txt", "w");
    char msg[] = "hello world";
    int fputout;

    for(int i = 0; i < strlen(msg); i++){
        fputc(msg[i], f);
    }

    putc('\n', f);

    putchar('x');

    /* both same as putchar */
    putc('\n', stdout);
    fputc('\n', stdout);

    return(0);
}
