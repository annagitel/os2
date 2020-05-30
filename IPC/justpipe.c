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

	}
}

int main() {
    int fd[2];
    pipe(fd);
    int flag = 0;
    int number = 0;

    pid_t pid;
    pid_t child = fork();
	while(number <6) {
		if (pid = fork()) {
			if (flag == 0) {
				printf("child sending %d to parent\n", number);
				write(fd[1], &number, sizeof(int));
				flag == 1;
			} else {
				read(fd[0], &number, sizeof(int));
				printf("child got  %d from parent\n", number);
				number = number + 1;
				printf("child sending %d to parent\n", number);
				write(fd[1], &number, sizeof(int));
			}
		} else {
			read(fd[0], &number, sizeof(int));
			printf("parent got %d from child\n", number);
			number = number + 1;
			printf("parent sending %d to child\n", number);
			write(fd[1], &number, sizeof(int));
		}
	}
    exit(0);
}


