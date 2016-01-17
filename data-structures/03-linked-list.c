#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    size_t indx;
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
void printList(Node * node){
    printf("%d %d\n", node->indx, node->a);
    if(node->next != NULL){
        printList(node->next);
    }
}

// insert a Node AFTER the i, i.e. the new node will be at
// position i+1 in the new list.
// O(n) time complexity
void insert(Node * node, Node * newnode, size_t i){
    bool final = (node->next == NULL);
    if(i == 0 || final){
        newnode->next = node->next;
        newnode->last = node;
        if(!final){
            node->next->last = newnode;
        }
        node->next = newnode;
    }
    else {
        insert(node->next, newnode, --i);
    }
}

// Remove the node indx steps from node
// O(n) time complexity
void splice(Node * node, size_t indx){
    if(indx > 0){
        if(node->next != NULL)
            splice(node->next, --indx);
    } else {
        node->last->next = node->next;
        if(node->next != NULL)
            node->next->last = node->last;
    }
}

// O(n) time complexity
void append(Node * node, Node * newnode){
    if(node->next == NULL){
        node->next = newnode;
        newnode->last = node;
        newnode->next = NULL;
    } else {
        append(node->next, newnode);
    }
}

// constant time complexity
void prepend(Node * oldroot, Node * newroot){

    // ptr to the new first element.
    // The root pointer is invariant, but the object changes.
    Node * a = oldroot;
    // ptr to the new second element
    Node * b = newroot;

    newroot->next = b;
    newroot->last = NULL;
    oldroot->last = a;
    oldroot->next->last = b;

    // Now I want to switch pointers

    // ptr to temporary newroot
    Node tmp = *newroot;
    // the first element is the newroot node
    *newroot = *oldroot;
    // the second element is the oldroot node
    *oldroot = tmp;
}

// O(n) time complexity
// Print the indx of the first node with given a
// If no match is found, return -1
int find(Node * node, int a){
    if(node->a == a){
        return(node->indx);
    } else if(node->next != NULL) {
        return(find(node->next, a)); 
    } else {
        return(-1);
    }
}

int main(){
    Node root;
    Node m;
    Node n;

    printf("Make and print list\n");
    makeList(&root, 5);
    printList(&root);

    printf("\nInsert 999 element after 2\n");
    m.indx=2; 
    m.a = 999;
    insert(&root, &m, 2);
    printList(&root);

    printf("\nInsert 888 element at the end\n");
    n.indx=6;
    n.a = 888;
    insert(&root, &n, 6);
    printList(&root);

    printf("\nRemove the 3rd element\n");
    splice(&root, 3);
    printList(&root);

    printf("\nAppend element 999\n");
    append(&root, &m);
    printList(&root);

    // This blows up into an infinite loop if you try to prepend a pointer to a Node
    // already in the list
    printf("\nPreprend a node, rerooting the list\n");
    splice(&root, 6);
    prepend(&root, &m);
    printList(&root);

    printf("\nindx of element with a=16 is %d\n", find(&root, 16));
    return(0);
}
