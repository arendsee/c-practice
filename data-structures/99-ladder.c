#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define NAME_LENGTH 20

#define GENOME 0
#define CHR    1
#define GENE   2
#define MRNA   3
#define CDS    4

#define NLEVELS 5

/*
typedef struct Match {
    Node * a;
    Node * b;
    size_t abeg;
    size_t aend;
    size_t bbeg;
    size_t bend;
    char strand;
} Match;


typedef struct Map {
    Node * a;
    Node * b;
} Map;


typedef struct Link {
    size_t size;
    Node * a;
    Node * b;
} Link;
*/

typedef struct Node {
    char name[NAME_LENGTH];
    size_t type;
    size_t beg;
    size_t end;
    size_t size;
    struct Node ** children;
    struct Node * next;
    struct Node * last;
} Node;

void printNode(Node * node){
    printf("name=%s type=%d beg=%d end=%d size=%d child=%x next=%x last=%x self=%x\n",
            node->name,
            node->type,
            node->beg,
            node->end,
            node->size,
            node->children,
            node->next,
            node->last,
            node);
}

/*
void deleteTree(Node * node){
    for(int i = 0; i < node->size; i++){
        deleteTree(node->children[i]);
    }
    free(node->children);
    free(node);
}
*/

void deleteList(Node * node){
    if(node->next != NULL){
        deleteList(node->next);
    }
    free(node);
}

Node * newNode(){
    Node * nd = (Node *) malloc(sizeof(Node));
    nd->type = 99;
    nd->beg = 0;
    nd->end = 0;
    nd->size = 0;
    nd->children = NULL;
    nd->next = NULL;
    nd->last = NULL;
    return(nd);
}

Node * readNodeFile(char * filename, size_t nlevels){
    FILE * fp = fopen(filename, "rb");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if(fp == NULL){
        printf("Cannot open file\n");
        exit(1);
    }
    
    // Define root node
    Node * root = newNode();
    strcpy(root->name, "root");
    root->type = GENOME;

    // This is a 3-pass algorithm, a little ugly, but it works.
    // Pseudocode
    //  1. create a doubly linked list of all Nodes, return final node
    //  2. iterate backwards, counting the children of each node, return first node
    //  3. iterate forwards, filling child arrays and trimming unnecessary links
    // NOTE: it is necessary to free this memory
    // NOTE: this leaks

    // create a flat, doubly-linked list of Node objects
    // the hierarchical level is stored in type {1, 2, ..., nlevels - 1)
    Node * lastnd = root;
    while ((read = getline(&line, &len, fp)) != EOF) {
        Node * nd = newNode();
        sscanf(line, "%*s %d %s %d %d", &nd->type, nd->name, &nd->beg, &nd->end);
        nd->last = lastnd;
        lastnd->next = nd;
        lastnd = nd;
        printNode(lastnd);
    }
    lastnd->next = NULL;

    printf("----\n");

    size_t counts[nlevels];
    for(int i = 0; i < nlevels; i++){
        counts[i] = 0;
    }

    Node * node = lastnd;
    while(node != NULL){

        counts[node->type]++;

        // if all children have been counted, set size
        if(node->next != NULL && node->type < node->next->type){
            node->size = counts[node->type + 1];
            counts[node->type + 1] = 0;
        }

        printNode(node);
        node = node->last; 
    }

    printf("----\n");

    Node * parents[nlevels];
    for(int i = 0; i < nlevels; i++){
        counts[i] = 0;
        parents[i] = NULL;
    }

    node = root;
    parents[0] = node;
    int pid;
    while(node != NULL){
        pid = node->type - 1;

        if(node->next != NULL){
            if(node->type < node->next->type){
                parents[node->type] = node;
                node->children = (Node**)malloc(node->size * sizeof(Node*));
                counts[node->type] = 0;
                node->next->last = NULL;
            }
        }

        // Here I seem to be writing to some weird place in memory, it is
        // overwriting STDOUT
        //parents[pid]->children[counts[pid]] = node;
        counts[node->type - 1]++;  

        printNode(node);
        node = node->next;
    }

    return(root);
}

int main(int argc, char* argv[]){

    Node * root = readNodeFile(argv[1], NLEVELS);

    return(0);
}
