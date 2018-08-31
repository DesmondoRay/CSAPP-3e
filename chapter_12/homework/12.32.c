/**
 * homework 12.32
 */

#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream);

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
	fd_set read_set;
	
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	FD_ZERO(&read_set);
	FD_SET(STDIN_FILENO, &read_set);
	
	Select(1, &read_set, NULL, NULL, &timeout);
	if (FD_ISSET(STDIN_FILENO, &read_set))
		s = fgets(s, size, stream);
	else
		return NULL;
	
	return s;
}