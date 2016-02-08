#ifndef __NODE_H__
#define __NODE_H__

#include "ia.h"

struct Node {
    unsigned int center;
    IA * by_start;
    IA * by_stop;
    struct Node * l_child;
    struct Node * r_child;
};

struct Node * init_node();

void free_node(struct Node *);

#endif
