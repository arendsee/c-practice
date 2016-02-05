#ifndef __INTERVAL_TREE_H__
#define __INTERVAL_TREE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef enum {lo, in, hi} Pos;
Pos point_overlap(uint, Interval);
struct Node * build_tree(IPA*, uint, uint);

#endif
