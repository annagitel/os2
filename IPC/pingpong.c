#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

int sighandler(int signum) {
    if (signum == SIGUSR1)
        return 1;
    return 0;
}
int main ()
{
    int  p2c[2], c2p[2], number;
    pipe(p2c);    //parent to child pipe
    pipe(c2p);    //child to parent pipe
    number = 0;

    pid_t father = getpid();
    printf("father pid: %d\n", father);
    pid_t child = fork();
    printf("child pid: %d\n", child);

    if (child == 0 )
    { //child process
        while(number < 6)
        {
            printf("in child process ");
            if(signal(SIGINT, sighandler) == 1)
                read(p2c[0], &number, sizeof(int));
            printf("%d\n", number);
            number = number + 1;
            write(c2p[1], &number, sizeof(int));
            kill(father,SIGUSR1);
        }
        close(p2c[0]); close(p2c[1]);
        close(c2p[0]); close(c2p[1]);
        exit(0);
    }
    else { //parent process
        while(number < 6)
        {
            printf("in parent process ");
            if(signal(SIGINT, sighandler) == 1)
                read(c2p[0], &number, sizeof(int));
            printf("%d\n", number);
            number = number + 1;
            write(p2c[1], &number, sizeof(int));
            kill(child,SIGUSR1);
        }
        close(p2c[0]); close(p2c[1]);
        close(c2p[0]); close(c2p[1]);
    }
    printf("Child is going to be terminated\n");
    printf("Parent is going to be terminated\n");
}

