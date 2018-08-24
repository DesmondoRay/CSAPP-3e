/* exercise 8.7 */

#include "../code/csapp.h"

unsigned int snooze(unsigned int secs);

void handler(int sig)
{
	return;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Need at least 1 argv.\n");
		exit(0);
	}
	
	if (signal(SIGINT, handler) == SIG_ERR)
		unix_error("signal error\n");
	
	snooze(atoi(argv[1]));
	
	return 0;
}