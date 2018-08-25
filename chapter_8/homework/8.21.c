/* homework 8.21 */

#include "../code/csapp.h"

int main()
{
	if (fork() == 0) {
		printf("a"); fflush(stdout);
		exit(0);
	}
	else {
		printf("b"); fflush(stdout);
		waitpid(-1, NULL, 0);
	}
	printf("c\n"); fflush(stdout);
	exit(0);
}

/* output: 
bac
*/

// possible ouput: bac, abc