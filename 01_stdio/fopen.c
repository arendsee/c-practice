#include <stdio.h>

int main(){

    FILE * f;
    FILE * g;
    char * f_file = "sample.txt";
    char * g_file = "non-existant-file.txt";

    /* "mode", the second argument, must be a string, not a character
     * mode may be any of the following:
     *  - "r"/"rb"         - read only
     *  - "w"/"wb"         - write only
     *  - "a"/"ab"         - write only, append to end
     *  - "r+"/"rb+"       - read and write
     *  - "w+"/"wb+"/"w+b" - read and write, truncate to zero length 
     *  - "a+"/"ab+"/"a+b" - read and write, append
     *
     *  The "b" indicates binary data, UNIX does not distinguish between binary and textual files.
     *
     *  If fopen succeeds, it returns a non-null FILE pointer, otherwise it returns NULL (defined in stdio.h)
     *
     */
    f = fopen(f_file, "r");
    g = fopen(g_file, "r");

    printf("%s open status: %d\n", f_file, f == NULL ? 0 : 1);
    printf("%s open status: %d\n", g_file, g == NULL ? 0 : 1);

    if(f != NULL)
        fclose(f);
    // If I don't do this check, I get a seg fault
    if(g != NULL)
        fclose(g);

    return(0);
}
