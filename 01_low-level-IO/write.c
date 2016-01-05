#include <unistd.h>
#include <stdlib.h>

/*
 * Write "hello", on a fail, write "fail
 */
int main(){
    int fildes = 1;         // STDOUT
    char * msg = "hello\n"; // text to write
    size_t nbytes = 6;      // length of msg
    if((write(fildes, msg, nbytes)) != nbytes) {
        int fildes = 2;        // STDERR
        char * msg = "fail\n"; // text to write
        size_t nbytes = 5;     // length of msg
        write(fildes, msg, nbytes);
    }
    exit(0);
}
