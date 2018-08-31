
#include "csapp.h"

void run_thread(void);
void *thread(void *vargp);
void run_process(void);

int main(void)
{
	clock_t start = clock();
	run_thread();
	clock_t end = clock();
	printf("run time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
	
	start = clock();
	run_process();
	printf("run time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
	end = clock();
}

void run_thread(void)
{
	int n = 2;
	int i;
	pthread_t tid[n];
	
	for (i = 0; i < n; i++)
		Pthread_create(&tid[i], NULL, thread, NULL);
	for (i = 0; i < n; i++)
		Pthread_join(tid[i], NULL);
	
	return;
}

void *thread(void *vargp)
{
	sleep(3);
	return NULL;
}

void run_process(void)
{
	pid_t pid;
	if ((pid = Fork()) == 0) {
		sleep(3);
		exit(0);
	}
	
	Wait(NULL);
	return;
}