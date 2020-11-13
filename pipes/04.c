#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    pid_t pid;
    char* message;
    int n;

    printf("starting\n");
    pid = fork();
    switch(pid){
        case -1:
            perror("fork failed\n"); 
            exit(1);
            break;
        case 0:
            // this child will become a zombie
            // see "<defunct>" entry with `ps ax`
            message = "child";
            n = 5;
            break;
        default:
            message = "parent";
            n = 15;
            break;
    }

    for(; n > 0; n--){
        printf("%s %d\n", message, pid);
        sleep(1);
    }
    
    exit(0);
}
