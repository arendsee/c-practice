#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "interval-tree.h"
#include "interval.h"
#include "node.h"
#include "ia.h"
#include "iv.h"

/* local function prototypes */
void print_node_verbosity_1(struct Node * n, int depth, char pos);
void print_node_verbosity_2(struct Node * n, int depth, char pos);
void print_node_verbosity_3(struct Node * n, int depth, char pos);
void print_node_r(struct Node * n, int depth, char pos, int verbosity);
uint get_center(IA *);
uint count_interval_overlaps_r(Interval *, struct Node *, uint);
uint count_point_overlaps_r(uint, struct Node *, uint);
IV * get_interval_overlaps_r(Interval *, struct Node *, IV *);
IV * get_point_overlaps_r(uint, struct Node *, IV *);




struct Node * build_tree(IA * intervals){
    /* initialize returned product */
    struct Node * node = init_node();

    node->center = get_center(intervals);

    /* array to store position of center point relative to each interval
     * in intervals
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
    IA * right    = init_set_ia(npos[lo]);
    IA * left     = init_set_ia(npos[hi]);
    node->by_start = init_set_ia(npos[in]);
    node->by_stop  = init_set_ia(npos[in]);

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
        free_ia(right);
    }

    if(npos[hi] > 0){
        node->l_child = build_tree(left);   
    } else {
        free_ia(left);
    }
    
    if(npos[in] > 0){
        qsort(&node->by_start->v[0], npos[in], sizeof(Interval), cmp_start);
        qsort(&node->by_stop->v[0],  npos[in], sizeof(Interval), cmp_stop);
    }

    free(pos);
    free_ia(intervals);

    return(node);
}



/**
 * Select a point at the center of the middle interval.
 * This guarantees at least one interval overlaps each node.
 * If the intervals are sorted, it also favors (but doesn't guarantee) a
 * balanced tree.
 */
uint get_center(IA * intr){
    // get the central index
    size_t i = intr->size / 2;
    // get the center point on this index
    uint x = (intr->v[i].stop - intr->v[i].start) / 2 + intr->v[i].start;
    return x;
}



uint count_point_overlaps_r(uint point, struct Node * node, uint count){
    if(point >= node->center) {
        for(int i = node->by_stop->size - 1; i >= 0 ; i--){
            if(point <= node->by_stop->v[i].stop){
                count++;
            } else {
                break;
            }
        }
        if(node->r_child)
            return count_point_overlaps_r(point, node->r_child, count);
    }
    else {
        for(int i = 0; i < node->by_start->size; i++){
            if(point >= node->by_start->v[i].start){
                count++;
            } else {
                break;
            }
        }
        if(node->l_child)
            return count_point_overlaps_r(point, node->l_child, count);
    }
    return count;
}

uint count_interval_overlaps_r(Interval * inv, struct Node * node, uint count){
    if(node == NULL)
        return count;

    Pos center_location = point_overlap(node->center, *inv);

    if(center_location == lo){
        for(int i = node->by_stop->size - 1; i >= 0 ; i--){
            if(inv->start <= node->by_stop->v[i].stop){
                count++;
            } else {
                break;
            }
        }
        return count_interval_overlaps_r(inv, node->r_child, count);
    }
    else if(center_location == hi){
        for(int i = 0; i < node->by_start->size; i++){
            if(inv->stop >= node->by_start->v[i].start){
                count++;
            } else {
                break;
            }
        }
        return count_interval_overlaps_r(inv, node->l_child, count);
    }
    else{
        count += node->by_start->size;
        return count_interval_overlaps_r(inv, node->r_child,
               count_interval_overlaps_r(inv, node->l_child, count));
    }
}

uint count_interval_overlaps(Interval * inv, struct Node * node){
    return count_interval_overlaps_r(inv, node, 0);
}

uint count_point_overlaps(uint point, struct Node * node){
    return count_point_overlaps_r(point, node, 0);
}



IV * get_point_overlaps_r(uint point, struct Node * node, IV * results){
    if(point >= node->center) {
        for(int i = node->by_stop->size - 1; i >= 0 ; i--){
            if(point <= node->by_stop->v[i].stop){
                iv_add(results, node->by_stop->v[i]);
            } else {
                break;
            }
        }
        if(node->r_child)
            return get_point_overlaps_r(point, node->r_child, results);
    }
    else {
        for(int i = 0; i < node->by_start->size; i++){
            if(point >= node->by_start->v[i].start){
                iv_add(results, node->by_start->v[i]);
            } else {
                break;
            }
        }
        if(node->l_child)
            return get_point_overlaps_r(point, node->l_child, results);
    }
    return results;
}

IV * get_interval_overlaps_r(Interval * inv, struct Node * node, IV * results){
    if(node == NULL)
        return results;

    Pos center_location = point_overlap(node->center, *inv);

    if(center_location == lo){
        for(int i = node->by_stop->size - 1; i >= 0 ; i--){
            if(inv->start <= node->by_stop->v[i].stop){
                iv_add(results, node->by_stop->v[i]);
            } else {
                break;
            }
        }
        return get_interval_overlaps_r(inv, node->r_child, results);
    }
    else if(center_location == hi){
        for(int i = 0; i < node->by_start->size; i++){
            if(inv->stop >= node->by_start->v[i].start){
                iv_add(results, node->by_start->v[i]);
            } else {
                break;
            }
        }
        return get_interval_overlaps_r(inv, node->l_child, results);
    }
    else{
        // TODO: This would be more efficient if I had an explicit function for
        // splicing an IV and IA
        //
        for(int i = 0; i < node->by_start->size; i++){
            iv_add(results, node->by_start->v[i]);
        }
        return get_interval_overlaps_r(inv, node->r_child,
               get_interval_overlaps_r(inv, node->l_child, results));
    }
}

IA * get_point_overlaps(uint point, struct Node * node){
    IV * results = get_point_overlaps_r(point, node, iv_init(8));
    IA * ia = init_ia();
    ia->size = results->size;
    ia->v = results->data;
    return ia;
}

IA * get_interval_overlaps(Interval * inv, struct Node * node){
    IV * results = get_interval_overlaps_r(inv, node, iv_init(8));
    // NOTE this does not free the excess memory, it only hides it
    // I could call realloc, or I could just pass back the IV
    IA * ia = init_ia();
    ia->size = results->size;
    ia->v = results->data;
    return ia;
}



/* write tree and center */
void print_node_verbosity_1(struct Node * n, int depth, char pos){
    printf("%*d - %c%d\n", depth * 2, depth, pos, n->center);
}

/* write tree, center, and start-sorted */
void print_node_verbosity_2(struct Node * n, int depth, char pos){
    printf("%*d   %*s\t%c%d:",
           depth * 2, depth, 
           10 - depth * 2, "", pos, n->center);
    for(int i = 0; i < n->by_start->size; i++){
        printf("(%u,%u) ",
               n->by_start->v[i].start,
               n->by_start->v[i].stop);
    }
    printf("\n");
}

/* write start- and stop-sorted vectors for each node */
void print_node_verbosity_3(struct Node * n, int depth, char pos){
    print_node_verbosity_1(n, depth, pos);
    for(int i = 0; i < n->by_start->size; i++){
        printf("\t\t(%u,%u) ",
               n->by_start->v[i].start,
               n->by_start->v[i].stop);
        printf("(%u,%u)\n",
               n->by_stop->v[i].start,
               n->by_stop->v[i].stop);
    }
}

/* local print function */
void print_node_r(struct Node * n, int depth, char pos, int verbosity){
    switch(verbosity){
        case 1:
            print_node_verbosity_1(n, depth, pos); break;
        case 2:
            print_node_verbosity_2(n, depth, pos); break;
        case 3:
            print_node_verbosity_3(n, depth, pos); break;
        default:
            fprintf(stderr, "verbosity must be 1, 2, or 3\n");
            exit(EXIT_FAILURE);
    }
    depth++;
    if(n->l_child){
        print_node_r(n->l_child, depth, 'l', verbosity);
    }
    if(n->r_child){
        print_node_r(n->r_child, depth, 'r', verbosity);
    }
}

/* public wrapper for real print function */
void print_node(struct Node * n, int verbosity){
    print_node_r(n, 0, 'c', verbosity);
}
