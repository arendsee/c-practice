/** Find overlapping intervals using a centered interval tree algorithm
 *
 * INPUT: a list of unsorted intervals
 */

#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "node.h"
#include "ia.h"
#include "interval.h"
#include "interval-tree.h"

int main(int argc, char ** argv){
    if(argc == 1){
        printf("USAGE: interval-tree <filename> <start> <stop>\n");
        exit(EXIT_FAILURE);
    }

    IA * ia = load_intervals(argv[1]);
    unsigned int start = atoi(argv[2]);
    unsigned int stop = atoi(argv[3]);

    struct Node * node = build_tree(ia);

    print_node(node, 3);

//    unsigned int count = count_point_overlaps(start, node, 0);
//    printf("%u\n", count);
    Interval inv = {.start=start, .stop=stop};
    IA * out = get_interval_overlaps(&inv, node);
    for(int i = 0; i < out->size; i++){
        printf("%u\t%u\n", out->v[i].start, out->v[i].stop);
    }

    free_node(node);
    exit(EXIT_SUCCESS);
}
