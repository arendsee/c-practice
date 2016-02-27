#include <stdio.h>
#include <string.h>

#define byte unsigned char

// Rotate one byte left
#define rotl(x) (x) << 1 ^ (x) >> 7
// Rotate one byte right
#define rotr(x) (x) >> 1 ^ (x) << 7

// Rotate k places on a block n bit long
#define grotl(x,n,k) (x) << ((k) % (n)) ^ (x) >> ((n) - ((k) % (n)))
#define grotr(x,n,k) (x) >> ((k) % (n)) ^ (x) << ((n) - ((k) % (n)))

void print_binary(void * data, size_t size){
    byte * v = (byte *) data;
    for(int i = 0; i < size; i++){
        for(byte mask = 128; mask != 0; mask >>= 1){
            printf("%d", v[i] & mask ? 1 : 0);
        }
        printf(" ");
    }
    printf("\n");
}

byte xor_all(void * data, size_t size, byte hash){
    byte * v = (byte *) data;
    hash = 0;
    for(int i = 0; i < size; i++){
        hash ^= v[i];
    }
    return(hash); 
}

int main(int argc, char * argv[]){
    char * a = "xor this line";
    print_binary(a, strlen(a) + 1);
    byte hash = 0;
    hash = xor_all(a, strlen(a), hash);
    print_binary(&hash, 1);
    byte b = 24;
    for(int i = 0; i < 8; i++){
        print_binary(&b, 1);
        b = rotl(b);
    }
    for(int i = 0; i < 8; i++){
        print_binary(&b, 1);
        b = rotr(b);
    }
    printf("\n");
    b = 24;
    for(int i = 0; i < 64; i++){
        print_binary(&b, 1);
        printf("%d\n", i % 8);
        b = grotr(b, 8, i);
    }
    return 0;
}
