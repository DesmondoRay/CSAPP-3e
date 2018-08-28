/**
 * homework 9.17
 *
 * 开发9.9.12节中的分配器的一个版本，执行下一次适配搜索，而不是首次适配搜索。
 */

#include "../../code/csapp.h"
#include "mm.h"
#include "memlib.h"

int main(void)
{
	int len = 10;
	char *str = (char *) mm_malloc(len);
	
	strcpy(str, "test-1 ok.\n");
	printf("%s", str);
	mm_free(str);
	
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

/* output: p4和p2指向的地址不同 
test-1 ok.
p1 = 0xdc193020
p2 = 0xdc193048
p3 = 0xdc193070
p4 = 0xdc193098
*/