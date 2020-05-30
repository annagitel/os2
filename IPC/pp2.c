//
// Created by asandler on 5/24/20.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

int flag = 0;

void my_handler(int signum){
    printf("***signal %d was detected***\n", signum);
    flag = 1;
}

int main (){
    pid_t father = getpid();
    pid_t child = fork();

    printf("    father pid: %d\n", father);
    printf("    child pid: %d\n", child);
    printf("    -----------\n");

    int  p[2], number;
    pipe(p);
    number = 0;

    signal(SIGUSR1, my_handler);

    printf("    child sending %d to parent\n",number);
    write(p[1], &number, sizeof(int));
    kill(father, SIGUSR1);
    while(1){
        printf("parent got %d from child\n", number);
        read(p[0], &number, sizeof(int));
        if (number == 5)
            exit(0);
        number = number + 1;
        printf("parent sending %d to child\n",number);
        write(p[1], &number, sizeof(int));
        kill(child,SIGUSR1);

        printf("child got  %d from parent\n", number);
        read(p[0], &number, sizeof(int));
        if (number == 5)
            exit(0);
        number = number + 1;
        printf("child sending %d to parent\n", number);
        write(p[1], &number, sizeof(int));
        kill(father, SIGUSR1);

    }

    close(p[0]); close(p[1]);
    printf("Child is going to be terminated\n");
    printf("Parent is going to be terminated\n");
    exit(0);
}

