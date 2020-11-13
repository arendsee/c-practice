#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void undying(int sig){
    printf("you can't kill me now ...\n");
    // ignore the SIGINT signal
    // After setting this, you can kill with ^Z and then `kill %1`, which will
    // send the Avada Kedavra of signals, SIGKILL
    (void) signal(SIGINT, SIG_IGN);
}

void ouch(int sig){
    printf("Try to kill me once ...\n");
    // reset the SIGING handling to the default handline
    (void) signal(SIGINT, SIG_DFL);
}

int main(int argc, char * argv[]){
    // set the handling for SIGINT to the custom "ouch" function
    (void) signal(SIGINT, ouch);
    int i = 0;
    while(1){
        sleep(1);
        printf("ping\n");
        i++;
        if (i > 2){
            (void) signal(SIGINT, undying);
        }
    }
    return 0;
}
