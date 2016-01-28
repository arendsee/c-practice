#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv){

    if(argc == 1){
        fprintf(stderr, "USAGE: minimal [-a] [-b ARG] [-c] <positionals>\n");
        exit(EXIT_FAILURE);
    }

    printf(" -- argv before being parsed by getopt\n");
    for(int i = 0; i < argc; i++){
        printf("ARGV%d: %s\n", i, argv[i]); 
    }

    printf("\n -- options in getopt loop\n");
    int opt;
    while((opt = getopt(argc, argv, "ab:c")) != -1){
        switch(opt) {
            case 'a':
                printf("see %c\n", opt);
                break;
            case 'b': 
                // This will swallow the following thing, even if it is
                // a bundled flag, e.g. -abc
                printf("see %c='%s'\n", opt, optarg);
                break;
            case 'c': 
                printf("see %c\n", opt);
                break;
            case '?':
                exit(EXIT_FAILURE);
        }
    }

    printf("\n -- variables\n");
    printf("argc:   %d\n", argc);
    printf("optind: %d\n", optind);

    /* Print unprocessed arguments, i.e. positional args. */
    printf("\n -- positional arguments\n");
    for(; optind < argc; optind++){
        printf("Positional: %s\n", argv[optind]);
    }

    printf("\n -- Here is argv after being parsed by getopt\n");
    for(int i = 0; i < argc; i++){
        printf("ARGV%d: %s\n", i, argv[i]); 
    }

    return(EXIT_SUCCESS);
}
