/* homework 8.24 */

#include "../../code/csapp.h"

#define N 2

int main()
{
	int status, i;
	pid_t pid;
	
	for (i = 0; i < N; i++)
		if ((pid = Fork()) == 0) {
			// 打开一个只读文件，并执行写操作
			FILE *fp = fopen("8.24_read_only.txt", "w");
			fprintf(fp, "read only.");
		}
	
	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (WIFEXITED(status))
			printf("child %d terminated normally with exit status = %d\n", 
				   pid, WEXITSTATUS(status));
		else if (WIFSIGNALED(status)) {
			int sig = WTERMSIG(status);
			char s[50];
			sprintf(s, "child %d terminated by signal %d", pid, sig);
			psignal(sig, s);
		}
	}
	
	if (errno != ECHILD)
		unix_error("waitpid error");
	
	exit(0);
}

/* output:
child 26487 terminated by signal 11: Segmentation fault
child 26488 terminated by signal 11: Segmentation fault
*/