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
    IPA * by_start;
    IPA * by_stop;
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

Node * init_node();
IPA * init_ipa();
void free_node(Node *);
Node * build_tree(IPA, uint center);

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

Node * init_node(){
    Node * node = (Node *)malloc(sizeof(Node));
    node->by_start = NULL;
    node->by_stop = NULL;
    node->l_child = NULL;
    node->r_child = NULL;
    return(node);
}

IPA * init_ipa(){
    IPA * ipa = (IPA *)malloc(sizeof(IPA));
    return(ipa);
}

void free_node(Node * node){
    if(l_child)
        free_node(l_child);
    if(r_child)
        free_node(r_child);
    if(by_start)
        free_ipa(by_start);
    if(by_stop)
        free_ipa(by_stop);
}

void free_IPA(IPA * ipa){
    for(int i = 0; i < ipa->size; i++){
        free(ipa->v[i]);
    }
    if(ipa->v)
        free(ipa->v);
}

Node * build_tree(IPA intervals, uint lower_bound, uint upper_bound){
    uint center = (upper_bound - lower_bound) / 2;
    uint lower_center = (center - lower_bound) / 2;
    uint upper_center = (upper_bound - center) / 2;
    Node * node = init_node();
    Pos * pos = (Pos *)malloc(intervals.size * sizeof(Pos));
    int npos[] = {0, 0, 0};
    for(int i = 0; i < intervals.size; i++){
        pos[i] = point_overlap(center, *intervals.v[i]);  
        npos[pos[i]]++;
        printf("%u\t%u\t%d\n", intervals.v[i]->start, intervals.v[i]->stop, pos[i]);
    }

    IPA * parts[3];
    for(int i = 0; i < 3; i++){
        if(npos[i] > 0){
            parts[i] = init_ipa();
            parts[i]->size = npos[i];
            parts[i]->v = (Interval **)maloc(npos[i] * sizeof(Interval *));
            switch(i){
                case lo;
                    node->l_child = build_tree(parts[i], lower_center, upper_bound);   
                    break;
                case in;
                    qsort(&parts[i]->v[0], npos[i], sizeof(Interval*), cmp_stop);
                    node->by_start = parts[i]->v;
                    node->by_stop = (Interval **)maloc(npos[i] * sizeof(Interval *));
                    memcpy(node->by_stop, node->by_start, npos[i] * sizeof(Interval *));
                    qsort(&node->by_stop->v[0], npos[i], sizeof(Interval*), cmp_stop);
                    break;
                case hi;
                    node->r_child = build_tree(parts[i], lower_bound, upper_center);   
                    break;
            }
        }
    }

    free(pos);
    
    return(node);
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
