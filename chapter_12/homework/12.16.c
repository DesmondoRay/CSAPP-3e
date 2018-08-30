/**
 * homework 12.16
 */

#include "csapp.h"
void *thread(void *vargp);

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", argv[0]);
		exit(0);
	}
	
	pthread_t tid;
	int i;
	int n = atoi(argv[1]);
	
	for (i = 0; i < n; i++)
		Pthread_create(&tid, NULL, thread, NULL);
	Pthread_exit(NULL);
}

void *thread(void *vargp)
{
	printf("Hello, world!\n");
	return NULL;
}