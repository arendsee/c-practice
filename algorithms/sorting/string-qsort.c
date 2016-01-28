#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct SS {
    char a_str[10];
};

int cmp_int(const void *ap, const void *bp){
    int a = * (int *) ap;
    int b = * (int *) bp;
    return(a - b);
}

int cmp_str(const void *ap, const void *bp){
    const char * a = * (char * const *) ap;
    const char * b = * (char * const *) bp;
    return(strcmp(a, b));
}

// Sort an SS structure by its string field a_str
int cmp_SS(const void *ap, const void *bp){
    const struct SS *a = * (struct SS * const *) ap;
    const struct SS *b = * (struct SS * const *) bp;
    return(strcmp(a->a_str, b->a_str));
}

int main(){
    char * char_arr[] = {"bbb", "abb", "zzz", "aaa"};
    int int_arr[] = {3,4,1,2};
    struct SS * SS_arr[4];

    for(int i = 0; i < 4; i++){
        SS_arr[i] = (struct SS *)malloc(sizeof(struct SS));
        strcpy(SS_arr[i]->a_str, char_arr[i]);
    }

    printf("Sorted char arrays\n");
    qsort(&char_arr[0], 4, sizeof(char*), cmp_str); 
    for(int i = 0; i < 4; i++){
        printf("%s\n", char_arr[i]);
    }

    printf("\nSorted integers\n");
    qsort(&int_arr[0], 4, sizeof(int), cmp_int); 
    for(int i = 0; i < 4; i++){
        printf("%d\n", int_arr[i]);
    }

    printf("\nSorted structure pointers\n");
    qsort(&SS_arr[0], 4, sizeof(struct SS*), cmp_SS); 
    for(int i = 0; i < 4; i++){
        printf("%s\n", SS_arr[i]->a_str);
    }

    // Free the structures
    for(int i = 0; i < 4; i++){
        free(SS_arr[i]);
    }

    return(0);
}
