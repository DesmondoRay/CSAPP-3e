/**
 * homework 9.18
 */

#include "../../code/csapp.h"
#include "mm.h"
#include "memlib.h"

int main(void)
{
	size_t size = 32;
	
	void *p1 = mm_malloc(size);
	printf("p1 = %#x\n", p1);
	void *p2 = mm_malloc(size);
	printf("p2 = %#x\n", p2);
	void *p3 = mm_malloc(size);
	printf("p3 = %#x\n", p3);
	mm_free(p2);
	void *p4 = mm_malloc(size);
	printf("p4 = %#x\n", p4);
	mm_free(p1);
	mm_free(p3);
	mm_free(p4);
	
	exit(0);
}

/* output:
p1 = 0x5e367020
p2 = 0x5e367048
p3 = 0x5e367070
p4 = 0x5e367048
*/