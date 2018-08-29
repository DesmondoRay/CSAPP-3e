/**
 * homework 10.7
 */

#include "csapp.h"

int main(int argc, char **argv)
{
	int n;
	char buf[MAXLINE];
	
	while ((n = Rio_readn(STDIN_FILENO, buf, MAXLINE)) != 0)
		Rio_writen(STDOUT_FILENO, buf, n);
	
	exit(0);
}