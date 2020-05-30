#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define MAX 5

int  p[2];

void my_handler(int signum){
    if (signum == SIGUSR1){

    }
}

int main (){
    pid_t father = getpid();
    pid_t child = fork();

    printf(" father pid: %d\n", father);
    printf(" child pid: %d\n", child);
    printf(" -----------\n");

    signal(SIGUSR1, my_handler);

    close(p[0]); close(p[1]);
    printf("Child is going to be terminated\n");
    printf("Parent is going to be terminated\n");
    exit(0);
}


