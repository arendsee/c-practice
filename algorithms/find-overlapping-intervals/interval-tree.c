/** Find overlapping intervals using a centered interval tree algorithm
 *
 * INPUT: a list of unsorted intervals
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned int uint;

typedef enum {lo, in, hi} Pos;

typedef struct {
    uint start;
    uint stop;
} Interval;

/** Interval pointer array */
typedef struct {
    size_t size;
    Interval ** v;
} IPA;

typedef struct {
    IPA by_start;
    IPA by_stop;
    struct Node * l_child;
    struct Node * r_child;
} Node;

int cmp_stop(const void *ap, const void *bp){
    Interval a = ** (Interval **) ap;
    Interval b = ** (Interval **) bp;
    return((a.stop > b.stop) - (b.stop > a.stop));
}

int cmp_start(const void *ap, const void *bp){
    Interval a = ** (Interval **) ap;
    Interval b = ** (Interval **) bp;
    return((a.start > b.start) - (b.start > a.start));
}

Pos point_overlap(uint, Interval);

Node * build_tree(IPA, uint center);
void free_tree(Node *);

size_t nlines(FILE *);


int main(int argc, char ** argv){
    FILE * int_file;
    size_t size;
    Interval ** intervals; 
    uint start, stop;
    Pos position;


    if(argc != 4){
        printf("USAGE: interval-tree <filename> <start> <stop>\n");
        exit(EXIT_FAILURE);
    }

    int_file = fopen(argv[1], "r");
    if(int_file == NULL){
        printf("Cannot open file '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    size = nlines(int_file);
    intervals = (Interval**)malloc(size * sizeof(Interval*));

    for(int i = 0; fscanf(int_file, "%d\t%d", &start, &stop) != EOF; i++){
        intervals[i] = (Interval*)malloc(sizeof(Interval));
        intervals[i]->start = start;
        intervals[i]->stop = stop;
    }

    IPA ipa = {.size = size, .v = intervals};
    build_tree(ipa, atoi(argv[2]));

    for(int i = 0; i < size; i++){
        free(intervals[i]);
    }
    free(intervals);
    fclose(int_file);
    exit(EXIT_SUCCESS);
}

Node * build_tree(IPA intervals, uint center){
    Node * node;
    Pos * pos = (Pos *)malloc(intervals.size * sizeof(Pos));
    int npos[] = {0, 0, 0};
    for(int i = 0; i < intervals.size; i++){
        pos[i] = point_overlap(center, *intervals.v[i]);  
        npos[pos[i]]++;
        printf("%u\t%u\t%d\n", intervals.v[i]->start, intervals.v[i]->stop, pos[i]);
    }

    /* TODO:
     * - Partition input intervals between left and
     *   right children and the intervals overlapping this node.
     * - Call build_tree with both children
     * - Check for stop conditions.  */

    IPA I_left;
    I_left.size = npos[lo];
    I_left.v = (Interval **)maloc(I_left.size * sizeof(Interval *));

    IPA I_center;
    I_center.size = npos[in];

    IPA I_right;
    I_right.size = npos[hi];

    free(pos);
    printf("lo=%d in=%d hi=%d\n", npos[0], npos[1], npos[2]);
    
    //qsort(&ipa.v[0], ipa.size, sizeof(Interval*), cmp_stop);
    return(node);
}

void free_tree(Node * node){
   // STUB
}

Pos point_overlap(uint a, Interval b){
    if(a < b.start){
        return lo;
    }
    else if(a > b.stop){
        return hi;
    }
    else{
        return in;
    }
}

Pos overlap(Interval a, Interval b){
    if(a.stop < b.start){
        return lo;
    }
    else if(a.start > b.stop){
        return hi;
    }
    else{
        return in;
    }
}

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
