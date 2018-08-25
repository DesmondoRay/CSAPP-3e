/* homework 8.20 */

#include "../code/csapp.h"

int main(int argc, char *argv[], char *env[])
{
	pid_t pid;
	int status;
	
	if ((pid = Fork()) == 0) {
		execve("/bin/ls", argv, env);
		exit(0);
	}
	
	if((pid = waitpid(pid, &status, 0)) > 0) {
		if (WIFEXITED(status))
			printf("child %d terminated normally with exit status = %d\n", 
				   pid, WEXITSTATUS(status));
		else
			printf("child %d terminated abnormally\n", pid);
	}
	
	exit(1);
}