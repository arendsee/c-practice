#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interval-tree.h"
#include "interval.h"
#include "node.h"
#include "ipa.h"

void print_node(struct Node * n){
    printf("%lu\n", n->by_start->size);
    if(n->l_child){
        printf("L-");
        print_node(n->l_child);
    }
    if(n->r_child){
        printf("R-");
        print_node(n->r_child);
    }
}

/**
 * Select a point at the center of the middle interval.
 * This guarantees at least one interval overlaps each node.
 * If the intervals are sorted, it also favors (but doesn't guarantee) a balanced tree.
 */
uint get_center(IPA * intr){
    // get the central index
    size_t i = intr->size / 2;
    // get the center point on this index
    uint x = (intr->v[i].stop - intr->v[i].start) / 2 + intr->v[i].start;
    return x;
}

struct Node * build_tree(IPA * intervals){
    /* initialize returned product */
    struct Node * node = init_node();

    node->center = get_center(intervals);

    /* array to store position of center point relative to each interval in intervals
     * lo = 0 -> interval is before the center
     * in = 1 -> interval overlaps the center
     * hi = 2 -> interval is after the center
     */
    Pos * pos = (Pos *)malloc(intervals->size * sizeof(Pos));

    /* count of intervals in each relative position */
    int npos[] = {0, 0, 0};

    /* iterate over intervals classifying and counting each */
    for(int i = 0; i < intervals->size; i++){
        pos[i] = point_overlap(node->center, intervals->v[i]);  
        npos[pos[i]]++;
    }

    /* initialise interval arrays */
    IPA * left     = init_set_ipa(npos[lo]);
    IPA * right    = init_set_ipa(npos[hi]);
    node->by_start = init_set_ipa(npos[in]);
    node->by_stop  = init_set_ipa(npos[in]);

    /* track index of interval to add */
    size_t lo_idx = 0;
    size_t in_idx = 0;
    size_t hi_idx = 0;

    /* assign intervals to appropriate partitions */
    for(size_t i = 0; i < intervals->size; i++){
        switch(pos[i]){
            case lo:
                left->v[lo_idx] = intervals->v[i];
                lo_idx++;
                break;
            case in:
                node->by_start->v[in_idx] = intervals->v[i];
                node->by_stop->v[in_idx]  = intervals->v[i];
                in_idx++;
                break;
            case hi:
                right->v[hi_idx] = intervals->v[i];
                hi_idx++;
                break;
            default:
                fprintf(stderr, "ERROR: something really weird happened ... sorry\n");
                exit(EXIT_FAILURE);
        }
    }

    if(npos[lo] > 0){
        node->l_child = build_tree(left);   
    } else {
        free_ipa(left);
    }

    if(npos[hi] > 0){
        node->r_child = build_tree(right);   
    } else {
        free_ipa(right);
    }
    
    if(npos[in] > 0){
        qsort(&node->by_start->v[0], npos[in], sizeof(Interval), cmp_start);
        qsort(&node->by_stop->v[0],  npos[in], sizeof(Interval), cmp_stop);
    }

    free(pos);
    free_ipa(intervals);

    return(node);
}

// TODO make this a proper tail recursion algorithm (how much does it matter)
// TODO remove duplication with function pointers, or something
uint count_point_overlaps(uint point, struct Node * node){
    uint count = 0;
    if(point >= node->center) {
        for(int i = 0; i < node->by_stop->size; i++){
            if(point <= node->by_stop->v[i].stop){
                count++;
            } else {
                break;
            }
        }
        count += count_point_overlaps(point, node->r_child);
    } else {
        for(int i = 0; i < node->by_start->size; i++){
            if(point >= node->by_start->v[i].start){
                count++;
            } else {
                break;
            }
        }
        count += count_point_overlaps(point, node->l_child);
    }
    return count;
}
