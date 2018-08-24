/* homework 8.13 */

#include "../code/csapp.h"

int main()
{
	int x = 3;
	
	if (Fork() != 0)
		printf("x=%d\n", ++x);
	
	printf("x=%d\n", --x);
	exit(0);
}

/*possible output: (x=4一定在x=3之前)
x=4
x=3
x=2
*/