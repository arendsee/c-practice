#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interval-tree.h"
#include "interval.h"
#include "node.h"
#include "ipa.h"

struct Node * build_tree(IPA * intervals, uint lower_bound, uint upper_bound){
    struct Node * node = init_node();
    Pos * pos;

    printf("Node N=%lu\n", intervals->size);

    uint center = (upper_bound - lower_bound) / 2;
    //uint lower_center = (center - lower_bound) / 2;
    //uint upper_center = (upper_bound - center) / 2;


    int npos[] = {0, 0, 0};
    if(intervals->size > 10){
        pos = (Pos *)malloc(intervals->size * sizeof(Pos));
    } else {
         
    }
    for(int i = 0; i < intervals->size; i++){
        pos[i] = point_overlap(center, *intervals->v[i]);  
        npos[pos[i]]++;
        //printf("%u\t%u\t%d\n", intervals->v[i]->start, intervals->v[i]->stop, pos[i]);
    }

    IPA * parts[3];
    for(int i = 0; i < 3; i++){
        if(npos[i] > 0){
            parts[i] = init_ipa();
            parts[i]->size = npos[i];
            parts[i]->v = (Interval **)malloc(npos[i] * sizeof(Interval *));
            if(i == in){
                node->by_start = parts[i];
                node->by_stop = init_ipa();
                node->by_stop->size = npos[i];
                node->by_stop->v = (Interval **)malloc(npos[i] * sizeof(Interval *));
                memcpy(node->by_stop->v, node->by_start->v, npos[i] * sizeof(Interval *));
            }
        }
    }

    size_t posid[] = {0, 0, 0};
    Pos p;
    for(int i = 0; i < intervals->size; i++){
        p = pos[i];
        parts[p]->v[posid[p]] = intervals->v[i];
        posid[p]++;
    }

    //node->l_child = build_tree(parts[lo], lower_center, upper_bound);   
    //node->r_child = build_tree(parts[hi], lower_bound, upper_center);   

    //qsort(&node->by_start->v[0], npos[in], sizeof(Interval*), cmp_start);
    //qsort(&node->by_stop->v[0],  npos[in], sizeof(Interval*), cmp_stop);

    if(pos)
        free(pos);

    return(node);
}
