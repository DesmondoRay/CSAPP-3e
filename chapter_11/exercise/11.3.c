/*
 * exercise 11.3
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Need at least 2 command line arguments.\n");
		exit(1);
	}
	
	unsigned n = 0;
	char *buf = argv[1];
	char *temp, *dot;
	while (buf[0]) {
		temp = buf;
		if ((dot = strchr(temp, '.')) != NULL) {
			buf = dot+1;
			*dot = '\0';
		}
		else if (( dot = strchr(temp, '\0')) != NULL)
			buf = dot;
		n = atoi(temp) + n * 0x100;
	}
	
	printf("%#x\n", n);
	exit(0);
}