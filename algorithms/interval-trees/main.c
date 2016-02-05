/** Find overlapping intervals using a centered interval tree algorithm
 *
 * INPUT: a list of unsorted intervals
 */

#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "interval-tree.h"

int main(int argc, char ** argv){
    if(argc != 4){
        printf("USAGE: interval-tree <filename> <start> <stop>\n");
        exit(EXIT_FAILURE);
    }

    IPA * ipa = load_intervals(argv[1]);

    build_tree(ipa, 0, atoi(argv[2]));

    free_ipa(ipa);
    exit(EXIT_SUCCESS);
}
