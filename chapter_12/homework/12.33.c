/**
 * homework 12.33
 */

#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream);
void *thread1(void *vargp);
void *thread2(void *vargp);

struct args {
	char *s;
	int size;
	FILE *stream;
	pthread_t *main_id;
};

static char *result = NULL;

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
	pthread_t tid1, tid2;
	struct args vargp;
	vargp.s = s;
	vargp.size = size;
	vargp.stream = stream;
	vargp.main_id = &tid2;
	
	Pthread_create(&tid1, NULL, thread1, (void *)&vargp);
	Pthread_create(&tid2, NULL, thread2, NULL);

	pthread_join(tid2, NULL);
	pthread_cancel(tid1);
	pthread_join(tid1, NULL);
	return result;
}

void *thread2(void *vargp)
{
	sleep(5);
	return NULL;
}

void *thread1(void *vargp)
{
	struct args *temp = (struct args *) vargp;
	result = fgets(temp->s, temp->size, temp->stream);
	
	pthread_t tid2 = *(temp->main_id);
	pthread_cancel(tid2);
	return NULL;
}