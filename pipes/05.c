#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    
    pid_t outcome;

    if(argc != 4){
        fprintf(stderr, "expected 3 arguments\n");
        exit(1);
    }


    // open argument 1 as the STDIN file
    if(!freopen(argv[1], "r", stdin)){
       fprintf(stderr, "failed to open input file\n"); 
    }

    // open argument 2 as the STDOUT file
    if(!freopen(argv[2], "w", stdout)){
       fprintf(stderr, "failed to open output file\n"); 
    }

    // open argument 3 as the STDERR file
    if(!freopen(argv[3], "w", stderr)){
       fprintf(stderr, "failed to open error file\n"); 
    }

    // `upper` will be executed with the same PID as the current process and
    // the file descriptors will opened above will stay open
    outcome = execl("./upper", "upper", 0);

    
    fprintf(stderr, "command 'upper' could not be found\n");
    return 1;
}
