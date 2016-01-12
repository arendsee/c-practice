#include <stdio.h>
#include <string.h>

int main(){
    FILE * f;
    char s[] = "ab\n";

    f = fopen("fflush.txt", "w");

    fwrite(s, sizeof(char), 2, f);

    // forces whatever data is in the datastream f to
    // be written immediately, before the assignment.
    fflush(f);
    s[0] = 'x';

    fwrite(s, sizeof(char), strlen(s), f);

    fclose(f);
    return(0);
}
