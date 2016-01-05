/*
 * Read from STDIN, echo to STDOUT
 */

#include <unistd.h>
#include <stdlib.h>

int main(){
    size_t buffer_size = 128;
    char buffer[buffer_size];
    int nread;
    int write_result;
    int fildes = 0; // STDIN

    // Catch the input
    nread = read(fildes, buffer, buffer_size);

    // Check read result
    if(nread == -1){
        write(2, "read fail\n", 10);
    }

    // Echo the input
    write_result = write(1, buffer, nread);

    // Check write result
    if(write_result != nread){
        write(2, "write fail\n", 11);
    }

    exit(0);
}
