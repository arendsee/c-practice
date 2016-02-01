#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MEGABYTE 1024 * 1024
#define SIZE 64 * 1024

void leak_all(){
    char ** data = (char**)calloc(SIZE, sizeof(char*));
    for(int i = 0; i < SIZE; i++){
        data[i] = (char*)calloc(MEGABYTE, 1); 
    }
    printf("%d %d\n", sizeof(data), strlen(data[100]));
}

void free_each(){
    char ** data = (char**)calloc(SIZE, sizeof(char*));
    for(int i = 0; i < SIZE; i++){
        data[i] = (char*)calloc(MEGABYTE, 1); 
        free(data[i]);
    }
    printf("%d %d\n", sizeof(data), strlen(data[100]));
}

int main(){
    free_each();
    while(1){}
}
