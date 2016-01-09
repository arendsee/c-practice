#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    int fildes;
    struct stat s;
    int status;

    fildes = open("open.out", O_RDONLY);

    status = fstat(fildes, &s);

    exit(0);
}
