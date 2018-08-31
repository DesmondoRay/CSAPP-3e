/**
 * homework 12.31
 */

#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream);
void handler(int sig);

jmp_buf buf;

int main(void)
{
	char buf[MAXLINE];
	
	if (tfgets(buf, MAXLINE, stdin) == NULL)
		printf("BOOM!\n");
	else
		printf("%s", buf);
	
	exit(0);
}

char *tfgets(char *s, int size, FILE *stream)
{
	pid_t pid;

	
	Signal(SIGCHLD, handler);
	
	if ((pid = Fork()) == 0) {
		sleep(5);
		exit(0);
	}
	
	if (sigsetjmp(buf, 1) == 0)
		s = fgets(s, size, stream);
	else 
		s = NULL;
	return s;
}

void handler(int sig)
{
	siglongjmp(buf, 1);
}