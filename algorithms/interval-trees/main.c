/** Find overlapping intervals using a centered interval tree algorithm
 *
 * INPUT: a list of unsorted intervals
 */

#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "interval-tree.h"
#include "ia.h"
#include "interval.h"
#include "itree.h"

int main(int argc, char ** argv){
    if(argc == 1){
        printf("USAGE: interval-tree <filename> <start> <stop>\n");
        exit(EXIT_FAILURE);
    }

    IA * ia = load_intervals(argv[1]);
    unsigned int start = atoi(argv[2]);
    unsigned int stop = atoi(argv[3]);

    struct IntervalTree * tree = build_tree(ia);

    print_interval_tree(tree, 3);

//    unsigned int count = count_point_overlaps(start, tree, 0);
//    printf("%u\n", count);
    Interval inv = {.start=start, .stop=stop};
    IA * out = get_interval_overlaps(&inv, tree);
    for(int i = 0; i < out->size; i++){
        printf("%u\t%u\n", out->v[i].start, out->v[i].stop);
    }

    free_interval_tree(tree);
    exit(EXIT_SUCCESS);
}
