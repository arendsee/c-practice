#ifndef __INTERVAL_TREE_H__
#define __INTERVAL_TREE_H__

#include "ipa.h"
#include "interval.h"
#include "node.h"

typedef unsigned int uint;

Pos point_overlap(unsigned int, Interval);

struct Node * build_tree(IPA*);

void print_node(struct Node*);

uint count_point_overlaps(uint, struct Node *);

#endif
