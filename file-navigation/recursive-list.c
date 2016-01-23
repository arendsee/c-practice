#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void list_dir(char * path, int level){
    DIR * d;
    struct dirent * entry;
    struct stat statbuf;
    if((d = opendir(path)) == NULL){
        fprintf(stderr, "Cannot open directory '%s'\n", path);
        return;
    }
    chdir(path);
    while((entry = readdir(d)) != NULL){
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)){
            // Descend into a directory if it is not "." or ".."
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                list_dir(entry->d_name, ++level); 
            }
        }
        else {
            printf("%s\n", entry->d_name);
        }
    }
    chdir("..");
    closedir(d);
}

void print_usage(){
    fprintf(stderr, "USAGE: recursive_list <directory name>\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]){
    if(argc == 1){
        print_usage();
    }
    list_dir(argv[1], 0);
    exit(EXIT_SUCCESS);
}
