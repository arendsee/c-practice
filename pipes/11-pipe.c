#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* function prototypes */
void die(const char*);

int main(int argc, char **argv) {
  int pdes[2];
  pid_t child;
 
  if(pipe(pdes) == -1)
    die("pipe()");
 
  child = fork();
  if(child == (pid_t)(-1))
          die("fork()"); /* fork failed */

  printf("child=%d; pdes[0]=%d; pdes[1]=%d\n", child, pdes[0], pdes[1]);

  if(child == (pid_t)0) {
          /* child process */

          close(1); /* close stdout */
          
          if(dup(pdes[1]) == -1)
            die("dup()");
          
          /* now stdout and pdes[1] are equivalent (dup returns lowest free descriptor) */

          if((execlp("ls", "ls", NULL)) == -1)
            die("execlp()");

    _exit(EXIT_SUCCESS);
  } else {
          /* parent process */

          close(0); /* close stdin */
          
          if(dup(pdes[0]) == -1)
            die("dup()");

          /* now stdin and pdes[0] are equivalent (dup returns lowest free descriptor) */

          if((execlp("wc", "wc", NULL)) == -1)
            die("execlp()");

    exit(EXIT_SUCCESS);
  }
 
  return 0;
}

void die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}
