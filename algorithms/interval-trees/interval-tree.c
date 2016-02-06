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

    uint center = (upper_bound - lower_bound) / 2 + lower_bound;
    //uint lower_center = (center - lower_bound) / 2;
    //uint upper_center = (upper_bound - center) / 2;


    int npos[] = {0, 0, 0};
    pos = (Pos *)malloc(intervals->size * sizeof(Pos));
    for(int i = 0; i < intervals->size; i++){
        pos[i] = point_overlap(center, intervals->v[i]);  
        npos[pos[i]]++;
    }

    IPA * parts[3];
    for(int i = 0; i < 3; i++){
        if(npos[i] > 0){
            size_t nbytes = npos[i] * sizeof(Interval);
            parts[i] = init_ipa();
            parts[i]->size = npos[i];
            parts[i]->v = (Interval *)malloc(nbytes);
            // If the interval overlaps the center point
            if(i == in){
                node->by_start = parts[i];
                node->by_stop = init_ipa();
                node->by_stop->size = npos[i];
                node->by_stop->v = (Interval *)malloc(nbytes);
                memcpy(&node->by_stop->v, &parts[i]->v, nbytes);
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

    // if stuff do this
    //node->l_child = build_tree(parts[lo], lower_center, upper_bound);   
    //node->r_child = build_tree(parts[hi], lower_bound, upper_center);   
    
    printf("%d\n", npos[in]);
    for(int i = 0; i < npos[in]; i++){
        printf("%d\t%d\n", node->by_stop->v[i].start, node->by_stop->v[i].stop);
    }

    printf("hi\n");
    qsort(&node->by_start->v[0], npos[in], sizeof(Interval), cmp_start);
    qsort(&node->by_stop->v[0],  npos[in], sizeof(Interval), cmp_stop);

    free_ipa(parts[0]);
    free_ipa(parts[2]);

    if(pos)
        free(pos);

    return(node);
}
