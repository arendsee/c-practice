#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

/* syntax for fread
size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);

Where
    * ptr    - a pointer to a data buffer (to fill)
    * size   - size of record in bytes
    * nitems - number of itmes (not bytes) to read
    * stream - a pointer to the input file stream (from fopen)

Functions returns the number of *items* successfully read

filestream -> buffer
*/

/* syntax for fwrite
size_t fwrite(void *ptr, size_t size, size_t nitems, FILE *stream);

Where
    * ptr    - a pointer to the data buffer (to read from)
    * size   - as in fread
    * nitems - as in fread
    * stream - a pointer to the output file stream (from fopen)

buffer -> filestream
*/

int main(){

    FILE *in, *out;
    char *infile = "sample.txt";
    char *outfile = "output.txt";
    int items_read;
    int items_writ;

    struct stat s;
    stat(infile, &s);

    size_t size = sizeof(char);
    size_t nitems = s.st_size / size;
    char buffer[size * nitems];

    in  = fopen(infile, "r");
    out = fopen(outfile, "w");

    if(out == NULL){
        printf("Cannot create %s\n", outfile);
    }
    if(in == NULL){
        printf("Cannot open %s\n", outfile);
    }

    items_read = fread(buffer, size, nitems, in);
    items_writ = fwrite(buffer, size, nitems, out);

    printf("items read: \t\t%d\n", items_read);
    printf("items writ: \t\t%d\n", items_writ);
    printf("file length (bytes): \t%d\n", nitems);
    printf("\nContents of buffer:\n-------------------\n%s",  buffer);

    return(0);
}
