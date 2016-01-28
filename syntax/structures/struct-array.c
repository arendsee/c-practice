#include <stdio.h>

#define SIZE 5


typedef struct G
{
    int a;
} G;


void setG(G * gs, size_t size){
    for(int i = 0; i < size; i++){
        gs[i].a = i;
    }
}


void printG(G * gs, size_t size){
    printf("Values stored in struct array\n");
    for(int i = 0; i < size; i++){
        printf("%d ", gs[i].a);
    }
    printf("\n\n");
    printf("The address of each struct in the array\n");
    for(int i = 0; i < size; i++){
        printf("%x ", &gs[i]);
    }
    printf("\n\n");
}


int main(){
    G g[SIZE];

    printf("Before initialization\n------\n");
    printG(g, SIZE);

    printf("\nAfter initialization\n------\n");
    setG(g, SIZE);
    printG(g, SIZE);
    return(0);
}
