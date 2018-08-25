/* homework 8.25 */

#include "../code/csapp.h"

jmp_buf buf;

void handler(int sig)
{
	Sio_puts("Time out. More than 5 seconds.\n");
	longjmp(buf, 1);
}

char *tfgets(char *s, int size, FILE *stream)
{
	alarm(5);
	Signal(SIGALRM, handler);
	if (setjmp(buf) == 0)
		fgets(s, size, stream);
	else
		return NULL;
	return s;
}

int main()
{
	char str[50];
	
	if (tfgets(str, 50, stdin) != NULL)
		printf("%s\n", str);

	return 0;
}