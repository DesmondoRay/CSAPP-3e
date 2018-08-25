/* homework 8.22 */

#include "../../code/csapp.h"

extern char ** environ;

int mysystem(char *command)
{
	pid_t pid;
	int status;
	
	if ((pid = Fork()) == 0) {
		char *argv[] = {"", "-c", command, NULL};
		execve("/bin/sh", argv, environ);
	}
	
	/* 传送SIGKILL信号给8.22_test2(一个无限循环的程序) */
	if (!strcmp(command, "./8.22_test2"))
		kill(pid, SIGKILL);
	
	if ((pid = waitpid(pid, &status, 0)) > 0) {
		if (WIFEXITED(status))
			return WEXITSTATUS(status);
	}
	
	if (WIFSIGNALED(status))
		return WTERMSIG(status);
}

int main(int argc, char *argv[])
{
	int status;
	
	status = mysystem("./8.22_test1");
	printf("%d\n", status);
	
	status = mysystem("./8.22_test2");
	printf("%d\n", status);
	
	exit(0);
}

/* output: 
8 
9 (注: SIGKILL的号码为9)
*/