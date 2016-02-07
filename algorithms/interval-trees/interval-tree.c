#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "interval-tree.h"
#include "interval.h"
#include "node.h"
#include "ipa.h"

/* local print function */
void print_node_r(struct Node * n, int depth, char pos){
    printf("%*d   %*s\t%c%d:",
           depth * 2, depth, 
           10 - depth * 2, "", pos, n->center);
    for(int i = 0; i < n->by_start->size; i++){
        printf("(%u,%u) ",
               n->by_start->v[i].start,
               n->by_start->v[i].stop);
    }
    printf("\n");
    depth++;
    if(n->l_child){
        print_node_r(n->l_child, depth, 'l');
    }
    if(n->r_child){
        print_node_r(n->r_child, depth, 'r');
    }
}

/* public wrapper for real print function */
void print_node(struct Node * n){
    print_node_r(n, 0, 'c');
}

/**
 * Select a point at the center of the middle interval.
 * This guarantees at least one interval overlaps each node.
 * If the intervals are sorted, it also favors (but doesn't guarantee) a
 * balanced tree.
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
     * lo = 0 -> center is lower than interval
     * in = 1 -> center is inside interval
     * hi = 2 -> center is higher than interval
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
    IPA * right    = init_set_ipa(npos[lo]);
    IPA * left     = init_set_ipa(npos[hi]);
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
                right->v[lo_idx] = intervals->v[i];
                lo_idx++;
                break;
            case in:
                node->by_start->v[in_idx] = intervals->v[i];
                node->by_stop->v[in_idx]  = intervals->v[i];
                in_idx++;
                break;
            case hi:
                left->v[hi_idx] = intervals->v[i];
                hi_idx++;
                break;
            default:
                fprintf(stderr, "ERROR: something really weird happened ... sorry\n");
                exit(EXIT_FAILURE);
        }
    }

    if(npos[lo] > 0){
        node->r_child = build_tree(right);   
    } else {
        free_ipa(right);
    }

    if(npos[hi] > 0){
        node->l_child = build_tree(left);   
    } else {
        free_ipa(left);
    }
    
    if(npos[in] > 0){
        qsort(&node->by_start->v[0], npos[in], sizeof(Interval), cmp_start);
        qsort(&node->by_stop->v[0],  npos[in], sizeof(Interval), cmp_stop);
    }

    free(pos);
    free_ipa(intervals);

    return(node);
}



uint count_point_overlaps(uint point, struct Node * node, uint count){
    assert(node != NULL);
    printf("%u %u\n", node->center, point);
    if(point >= node->center) {
        assert(node->by_stop != NULL);
        assert(node->by_stop->v != NULL);
        assert(node->by_stop->size > 0);
        for(int i = node->by_stop->size; i != 0 ; i--){
            printf("a\n");
            printf("%u\n",node->by_stop->v[i].stop); 
            printf("b\n");
            if(point <= node->by_stop->v[i].stop){
                printf("add\n");
                count++;
            } else {
                break;
            }
        }
        if(node->r_child)
            return count_point_overlaps(point, node->r_child, count);
    } else {
        assert(node->by_start != NULL);
        assert(node->by_start->v != NULL);
        assert(node->by_start->size > 0);
        for(int i = 0; i < node->by_start->size; i++){
            break;
            if(point >= node->by_start->v[i].start){
                printf("add\n");
                count++;
            } else {
                break;
            }
        }
        if(node->l_child != NULL)
            return count_point_overlaps(point, node->l_child, count);
    }
    return count;
}
