/*
 * exercise 11.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Need at least 2 command line arguments.\n");
		exit(1);
	}
	
	unsigned n = htonl(strtol(argv[1], NULL, 16));
	char *p = (char *) malloc(16);
	inet_ntop(AF_INET, &n, p, 16);
	printf("%s\n", p);
	
	exit(0);
}