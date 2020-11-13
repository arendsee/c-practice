#include <unistd.h>

int main(int argc, char * argv[]){
    execvp("ps", argv);
    return 0;
}
