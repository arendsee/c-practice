#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv){
    int fildes;
    struct stat s;
    mode_t modes;

    stat(argv[1], &s);

    modes = s.st_mode;

    printf("File Size: \t\t%d bytes\n", s.st_size);
    printf("Number of Links: \t%d\n",   s.st_nlink);
    printf("File inode: \t\t%d\n",      s.st_ino);
    printf("st_dev: \t\t%d\n",          s.st_dev);
    printf("st_uid: \t\t%d\n",          s.st_uid);
    printf("st_gid: \t\t%d\n",          s.st_gid);
    printf("st_atime \t\t%d\n",         s.st_atime);
    printf("st_ctime \t\t%d\n",         s.st_ctime);
    printf("st_mtime \t\t%d\n",         s.st_mtime);

    // is special block device
    printf("S_ISBLK \t\t%d\n",  S_ISBLK(modes)  ? 1 : 0);
    // character special file
    printf("S_ISCHR \t\t%d\n",  S_ISCHR(modes)  ? 1 : 0);
    // is directory
    printf("S_ISDIR \t\t%d\n",  S_ISDIR(modes)  ? 1 : 0);
    // is FIFO
    printf("S_ISFIFO \t\t%d\n", S_ISFIFO(modes) ? 1 : 0);
    // is a regular file
    printf("S_ISREG \t\t%d\n",  S_ISREG(modes)  ? 1 : 0);
    // is a symbolic link
    printf("S_ISLNK \t\t%d\n",  S_ISLNK(modes)  ? 1 : 0);


    printf("Permissions:\t\t");
    // d---------
    printf( S_ISDIR(modes)   ? "d" : "-");
    // -r--------
    printf((modes & S_IRUSR) ? "r" : "-");
    // --w-------
    printf((modes & S_IWUSR) ? "w" : "-");
    // ---x------
    printf((modes & S_IXUSR) ? "x" : "-");
    // ----r-----
    printf((modes & S_IRGRP) ? "r" : "-");
    // -----w----
    printf((modes & S_IWGRP) ? "w" : "-");
    // ------x---
    printf((modes & S_IXGRP) ? "x" : "-");
    // -------r--
    printf((modes & S_IROTH) ? "r" : "-");
    // --------w-
    printf((modes & S_IWOTH) ? "w" : "-");
    // ---------x
    printf((modes & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    exit(0);
}
