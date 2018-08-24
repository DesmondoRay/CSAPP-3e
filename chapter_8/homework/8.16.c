/* homework 8.16 */

#include "../code/csapp.h"
int counter = 1;

int main()
{
	if (fork() == 0) {
		counter--;
		exit(0);
	}
	else {
		Wait(NULL);
		printf("counter = %d\n", ++counter);
	}
	exit(0);
}

/* output:
counter = 2
*/