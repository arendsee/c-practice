#ifndef __NODE_H__
#define __NODE_H__

#include "ipa.h"

struct Node {
    IPA * by_start;
    IPA * by_stop;
    struct Node * l_child;
    struct Node * r_child;
};

struct Node * init_node();

void free_node(struct Node *);

#endif
