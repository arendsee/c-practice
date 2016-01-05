#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

    int fildes = 0;

    // create a 600 file
    fildes = open("delete-me",
                  O_CREAT | O_EXCL,
                  S_IRUSR | S_IWUSR | S_IWOTH);

    /*
     * The requested permissions (-rw-----w-) are ORed with the user mask, on
     * my system at least, this results in denial of open's request for write
     * permissions for OTHERS
     */

    if(fildes == -1){
        write(2, "fail\n", 5);
    }

    // This is a hacky way of returning an integer
    exit(fildes);
}
