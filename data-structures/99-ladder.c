#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <glib.h>

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
    char type;
    size_t beg;
    size_t end;
    size_t size;
    struct Node * children;
    struct Node * next;
    struct Node * last;
} Node;


(Node *) readNodeFile(char * filename, size_t nlevels){
    FILE * fp = fopen(filename, "rb");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if(fp == NULL){
        printf("Cannot open file\n");
        exit(1);
    }
    
    char * type;
    size_t level;
    char * name;
    size_t beg;
    size_t end;

    // Define root node
    Node node;
    node.type = GENOME;
    node.size = 0;
    node.last = NULL;
    node.beg = 0;
    node.end = 0;

    // create a flat, doubly-linked list of Node objects
    // the hierarchical level is stored in type {1, 2, ..., nlevels - 1)
    Node * lastnd = &node;
    while ((read = getline(&line, &len, fp)) != EOF) {
        Node nd; // new node
        sscanf(line, "%*s %c %s %d %d", &nd.type, &nd.name, &nd.beg, &nd.end);
        nd.last = lastnd;
        lastnd->next = &nd;
        lastnd = &nd;
    }
    lastnd->next = NULL;

    size_t counts[n_levels];
    for(int i = 0; i < n_levels; i++){
        counts[i] = 0;
    }

    /*
    // work backwards, raising the hierarchy
    size_t prior_level = 0;
    while(lastnd->last != NULL){
         
    }
    */
}

int main(int argc, char* argv[]){

    readNodeFile(argv[1], NLEVELS);

    return(0);
}
