#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
int fd[2], number;
pid_t pid;

void son_handler(int signum){
	if (signum == SIGUSR1){
		read(fd[0], &number, sizeof(int));
		printf("%d\n",number);
		//printf("child got %d from parent\n", number);
		number = number + 1;
		if (number == 6){
			printf("Child is going to be terminated\n");
			exit(0);
		}
		//printf("child sending %d to parent\n", number);
		write(fd[1], &number, sizeof(int));
		kill(getppid(),SIGUSR1);
	}
}

void father_handler(int signum){
	if (signum == SIGUSR1){
		read(fd[0], &number, sizeof(int));
		printf("%d\n",number);
		//printf("parent got  %d from child\n", number);
		number = number + 1;
		//printf("parent sending %d to child\n", number);
		write(fd[1], &number, sizeof(int));
		kill(pid,SIGUSR1);
	}
}

int main() {
	number = 0;
	pipe(fd);
	pid = fork();

	if(!pid) { //first child sends
		//printf("child sending %d to parent\n", number);
		write(fd[1], &number, sizeof(int));
		kill(getppid(), SIGUSR1);
	}

	if (pid) { //parent
		while (1) {
			signal(SIGUSR1, father_handler);
			if(wait(NULL)) {
				printf("Parent is going to be terminated\n");
				close(fd[0]);
				close(fd[1]);
				exit(0);
			}
		}
	}
	else { //child
		while (1){
			signal(SIGUSR1, son_handler);
		}
	}
}
