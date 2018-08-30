/**
 * homework 12.17
 */

// A. 主线程没有等待其他线程终止，就直接终止了

#include "csapp.h"
void *thread(void *vargp);

int main()
{
	pthread_t tid;
	
	Pthread_create(&tid, NULL, thread, NULL);
	Pthread_exit(NULL);
}

void *thread(void *vargp)
{
	Sleep(1);
	printf("Hello, world!\n");
	return NULL;
}