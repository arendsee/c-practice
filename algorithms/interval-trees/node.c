#include <stdlib.h>

#include "node.h"
#include "ipa.h"

struct Node * init_node(){
    struct Node * node = (struct Node *)malloc(sizeof(struct Node));
    node->by_start = NULL;
    node->by_stop  = NULL;
    node->l_child  = NULL;
    node->r_child  = NULL;
    return(node);
}
void free_node(struct Node * node){
    if(node->l_child)
        free_node(node->l_child);
    if(node->r_child)
        free_node(node->r_child);
    if(node->by_start)
        free_ipa(node->by_start);
    if(node->by_stop)
        free_ipa(node->by_stop);
    if(node)
        free(node);
}
