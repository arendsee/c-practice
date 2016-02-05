#include "io.h"
#include "interval-tree.h"

/* Private function for counting lines in a file */
size_t nlines(FILE * fp){
    rewind(fp);
    char * lineptr = NULL;
    size_t n = 0;
    size_t nlines = 0;
    while(getline(&lineptr, &n, fp) != EOF){
        nlines++; 
    }
    rewind(fp);
    free(lineptr);
    return nlines;
}

IPA * load_intervals(char * filename){
    FILE * int_file;
    size_t size;
    Interval ** intervals; 
    uint start, stop;
    int_file = fopen(filename, "r");

    if(int_file == NULL){
        printf("Cannot open file '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    size = nlines(int_file);
    intervals = (Interval**)malloc(size * sizeof(Interval*));

    /* WARNING: This loop assumes the file is formated with one pair of
     * integers on each line. No checking for this is done. If this function is
     * ported to production code, be sure to implement a check. */
    for(int i = 0; fscanf(int_file, "%d\t%d", &start, &stop) != EOF; i++){
        intervals[i] = (Interval*)malloc(sizeof(Interval));
        intervals[i]->start = start;
        intervals[i]->stop = stop;
    }

    IPA ipa = {.size = size, .v = intervals};

    return(&ipa);
}
