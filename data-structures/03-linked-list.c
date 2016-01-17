#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int indx;
    int a; // Just a thing to set
    struct Node * next;
    struct Node * last;
} Node;

// Leaks memory, see NOTE
void makeList(Node * root, size_t length){
    root->indx = 0;
    root->last = NULL;
    root->a = 0;
    Node * last = root;
    for(int i = 1; i < length; i++){
        // NOTE: This will leak memory if not freed
        Node * cptr = (Node *) malloc(sizeof(Node));
        cptr->last = last;
        cptr->next = NULL;
        cptr->indx = i;
        cptr->a = i * i; // for no particular reason
        // link previous node to this one
        last->next = cptr;
        last = cptr;
    }
}

// recursive print through all the nodes
void printList(Node node){
    printf("%d %d\n", node.indx, node.a);
    if(node.next != NULL){
        printList(*(node.next));
    }
}

// insert a Node BEFORE the indx, i.e. the new node will be at
// position indx in the new list.
void insert(Node * node, Node * newnode, size_t indx){
    Node * n = node;
    int iid; // insertion id
    for(iid = 0; iid < indx; iid++){
        if(n->next == NULL){
            newnode->last = n;
            newnode->next = NULL;
            n->next = newnode;
            return;
        }
        n = n->next;
    }
    if(n != NULL){
        newnode->last = n->last;
        newnode->next = n;
        n->last->next = newnode;
        n->last = newnode;
    }
}

void splice(Node root, size_t indx){

}

void append(Node root, Node newnode){

}

void prepend(Node root, Node newnode){

}

int find(Node root, int a){

}

int main(){
    Node root;
    Node m;
    Node n;

    makeList(&root, 5);
    printList(root);

    printf("\n");
    m.indx=2; 
    m.a = 999;
    insert(&root, &m, 2);
    printList(root);

    printf("\n");
    n.indx=6;
    n.a = 888;
    insert(&root, &m, 6);
    printList(root);
    return(0);
}
