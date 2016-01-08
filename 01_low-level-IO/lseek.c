#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    int fildes;
    off_t start;
    size_t bs = 8;
    char buffer[bs];

    fildes = open("sample.txt", O_RDONLY);

    lseek(fildes, 1, SEEK_SET);
    read(fildes, buffer, 2); 
    write(fildes, buffer, 2);

    lseek(fildes, 2, SEEK_CUR);
    read(fildes, buffer, 2); 
    write(fildes, buffer, 2);

    lseek(fildes, 0, SEEK_END);
    read(fildes, buffer, 2); 
    write(fildes, buffer, 2);

    close(fildes);
    exit(0);
}
