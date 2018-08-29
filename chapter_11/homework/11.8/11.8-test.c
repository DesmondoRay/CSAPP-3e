/* 11.8-test.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int i;
	
	fprintf(stdout, "test start\n");
	for (i = 0; i < 5; i++) {
		sleep(1);
		fprintf(stdout, "running...\n");
		fflush(stdout);
	}
	fprintf(stdout, "test done!\n");
	exit(0);
}