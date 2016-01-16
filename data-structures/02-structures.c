#include <stdio.h>


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
    size_t size = 5;
    G g[size];
    printG(g, size);
    setG(g, size);
    printG(g, size);
    return(0);
}
