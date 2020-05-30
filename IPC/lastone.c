//
// Created by asandler on 5/29/20.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
void my_handler(int signum){
	if (signum == SIGUSR1){
		printf("sig 1111111111\n");
	}
	if (signum == SIGUSR2){
		printf("sig 2222222222\n");

	}
}

int main() {
	int fd[2];
	pipe(fd);
	int flag = 0;
	int number = 0;

	printf("fuckkkkkkkkkkkkkkkkkk\n");
	pid_t pid = fork();

	if(!pid) { //first child sends
		printf("child sending %d to parent\n", number);
		write(fd[1], &number, sizeof(int));
		kill(getppid(), SIGUSR1);
	}

	while(number <6) {
		if (pid) { //parent
			signal(SIGUSR1, my_handler);
			read(fd[0], &number, sizeof(int));
			printf("parent got  %d from child\n", number);
			number = number + 1;
			printf("parent sending %d to child\n", number);
			write(fd[1], &number, sizeof(int));
			kill(getppid(),SIGUSR2);
			sleep(2);
		}

		else {
			signal(SIGUSR2, my_handler);
			read(fd[0], &number, sizeof(int));
			printf("child got %d from parent\n", number);
			number = number + 1;
			printf("child sending %d to parent\n", number);
			write(fd[1], &number, sizeof(int));
			kill(0,SIGUSR1);
			sleep(2);
		}
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}


