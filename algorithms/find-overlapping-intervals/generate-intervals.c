#include <stdlib.h>
#include <stdio.h>

#define WIDTH 1000
#define INTERVAL_WIDTH 100
#define N_INTERVALS 100
#define RAND (int)((double) rand() / RAND_MAX * (WIDTH - INTERVAL_WIDTH))

int main(void){
    int i=0;
    int start, stop;

    // NOTE: I am not setting a random seed

    while(i++ < N_INTERVALS){
        start = RAND;
        stop = start + INTERVAL_WIDTH - 1;
        printf("%d\t%d\n", start, stop); 
    }

    exit(EXIT_SUCCESS);
}
