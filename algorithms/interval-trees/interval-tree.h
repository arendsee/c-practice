#ifndef __INTERVAL_TREE_H__
#define __INTERVAL_TREE_H__

#include "ia.h"
#include "interval.h"
#include "node.h"

typedef unsigned int uint;

Pos point_overlap(unsigned int, Interval);

struct Node * build_tree(IA*);

void print_node(struct Node*, int verbosity);

uint count_point_overlaps(uint, struct Node *);

uint count_interval_overlaps(Interval *, struct Node *);

IA * get_point_overlaps(uint, struct Node *);

IA * get_interval_overlaps(Interval *, struct Node *);

#endif
