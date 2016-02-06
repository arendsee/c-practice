#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interval-tree.h"
#include "interval.h"
#include "node.h"
#include "ipa.h"

struct Node * build_tree(IPA * intervals, uint lower_bound, uint upper_bound){
    /* initialize returned product */
    struct Node * node = init_node();

    uint center       = (upper_bound - lower_bound) / 2 + lower_bound;
    uint lower_center = (center      - lower_bound) / 2 + lower_bound;
    uint upper_center = (upper_bound - center)      / 2 + center;

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
        pos[i] = point_overlap(center, intervals->v[i]);  
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
        node->l_child = build_tree(left, lower_center, upper_bound);   
    } else {
        free_ipa(left);
    }

    if(npos[hi] > 0){
        node->r_child = build_tree(right, lower_bound, upper_center);   
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
