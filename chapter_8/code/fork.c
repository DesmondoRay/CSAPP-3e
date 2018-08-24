#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	pid_t pid;
	int x = 1;
	
	pid = fork();
	if (pid == 0) {
		printf("child : x = %d\n", ++x);
		printf("child id: %d\n", getpid());
		printf("parent id: %d\n", getppid());
		exit(0);
	}
	
	printf("parent: x = %d\n", --x);
	exit(0);
}