#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interval-tree.h"
#include "interval.h"
#include "node.h"
#include "ipa.h"

typedef unsigned int uint;

struct Node * build_tree(IPA * intervals, uint lower_bound, uint upper_bound){
    uint center = (upper_bound - lower_bound) / 2;
    uint lower_center = (center - lower_bound) / 2;
    uint upper_center = (upper_bound - center) / 2;
    struct Node * node = init_node();
    Pos * pos = (Pos *)malloc(intervals->size * sizeof(Pos));
    int npos[] = {0, 0, 0};
    for(int i = 0; i < intervals->size; i++){
        pos[i] = point_overlap(center, *intervals->v[i]);  
        npos[pos[i]]++;
        printf("%u\t%u\t%d\n", intervals->v[i]->start, intervals->v[i]->stop, pos[i]);
    }

    IPA * parts[3];
    for(int i = 0; i < 3; i++){
        if(npos[i] > 0){
            parts[i] = init_ipa();
            parts[i]->size = npos[i];
            parts[i]->v = (Interval **)malloc(npos[i] * sizeof(Interval *));
            switch(i){
                case lo:
                    node->l_child = build_tree(parts[i], lower_center, upper_bound);   
                    break;
                case in:
                    qsort(&parts[i]->v[0], npos[i], sizeof(Interval*), cmp_stop);
                    node->by_start = parts[i];
                    node->by_stop = init_ipa();
                    node->by_stop->size = npos[i];
                    node->by_stop->v = (Interval **)malloc(npos[i] * sizeof(Interval *));
                    memcpy(node->by_stop->v, node->by_start->v, npos[i] * sizeof(Interval *));
                    qsort(&node->by_stop->v[0], npos[i], sizeof(Interval*), cmp_stop);
                    break;
                case hi:
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
