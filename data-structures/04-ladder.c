#include <stdio.h>

typedef struct Node {
    char name[50];
    char type[10];
    size_t beg;
    size_t end;
    struct Node * parent;
    size_t size;
    struct Node * children;
} Node;


typedef struct Match {
    Node * a;
    Node * b;
    size_t abeg;
    size_t aend;
    size_t bbeg;
    size_t bend;
    char strand;
} Match;


typedef struct Flat {
    size_t size;
    struct Node * children; 
} Flat;


typedef struct Map {
    Node * a;
    Node * b;
} Map;


typedef struct Link {
    Node * a;
    size_t size;
    Node * b;
} Link;



int main(){
    return(0);
}
