#include <stdio.h>
#include <string.h>

void print_bitwise_operators(char a, char b){
    printf("%x AND %x = %x\n", a, b, a & b);
    printf("%x OR  %x = %x\n", a, b, a | b);
    printf("%x XOR %x = %x\n", a, b, a ^ b);
    printf("%x << 1  = %x\n", a, a << 1);
    printf("1 << 1  = %x\n", 1 << 1);
    printf("2 << 1  = %x\n", 2 << 1);
    printf("4 << 1  = %x\n", 4 << 1);
    printf("8 << 1  = %x\n", 8 << 1);
}

void print_binary(char * data, size_t n){
    for(int i = 0; i < n; i++){
        for(char offset = 1; offset != 128; offset = offset << 1){
            printf("%d", data[i] & offset ? 1 : 0);
        }
        printf(" ");
    }
    printf("\n");
}

int main(int argc, char * argv[]){
    char * a = "A string to hash";
    print_binary(a, strlen(a));
    print_bitwise_operators(60, 61);
    return 0;
}
