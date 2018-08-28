/**
 * homework 9.20
 */

#include "../../code/csapp.h"
#include "mm.h"
#include "memlib.h"

#define TIMES 7500
#define FIRST (TIMES * 2 / 3)
#define LAST (TIMES / 3)

/* 测试标准C库的malloc */
void test_malloc(int array[], size_t total_size)
{
	int i;
	void **ptr = malloc(TIMES * sizeof(void *));
	void *addr_start = sbrk(0);
	clock_t time_start = clock();
	for (i = 0; i < FIRST; i++)
		ptr[i] = malloc(array[i]);
	for (i = 0; i < FIRST; i+=2) {
		free(ptr[i]);
		total_size -= array[i];
	}
	for (i = FIRST; i < LAST; i++) 
		ptr[i] = malloc(array[i]);
	void *addr_end = sbrk(0);
	
	for (i = 1; i < FIRST; i+=2)
		free(ptr[i]);
	for (i = FIRST; i < LAST; i++)
		free(ptr[i]);
	clock_t time_end = clock();
	printf("run time(seconds): %lf\n", difftime(time_end, time_start)/CLOCKS_PER_SEC);
	size_t heap = addr_end-addr_start;
	printf("malloc size(bytes): %lu, heap size: %lu\n", total_size, heap);
}

/* 测试homework 9.17 的malloc */
void test_mm_malloc(int array[], size_t total_size)
{
	int i;
	void **ptr = malloc(TIMES * sizeof(void *));
	void *temp = mm_malloc(1); // 用于初始化，若不初始化，addr_start == 0；
	mm_free(temp);
	
	void *addr_start = mem_sbrk(0);
	clock_t time_start = clock();
	for (i = 0; i < FIRST; i++)
		ptr[i] = mm_malloc(array[i]);
	for (i = 0; i < FIRST; i+=2) {
		mm_free(ptr[i]);
		total_size -= array[i];
	}
	for (i = FIRST; i < LAST; i++) 
		ptr[i] = mm_malloc(array[i]);
	void * addr_end = mem_sbrk(0);
	
	for (i = 1; i < FIRST; i+=2)
		mm_free(ptr[i]);
	for (i = FIRST; i < LAST; i++)
		mm_free(ptr[i]);
	clock_t time_end = clock();
	printf("run time(seconds): %lf\n", difftime(time_end, time_start)/CLOCKS_PER_SEC);
	size_t heap = addr_end-addr_start;
	printf("malloc size(bytes): %lu, heap size: %lu\n", total_size, heap);
}

int main(void)
{
	int array[TIMES];
	int i;
	size_t total_size = 0;
	srand(time(0));
	
	for (i = 0; i < TIMES; i++) {
		array[i] = rand() % 1000;
		total_size += array[i];
	}
	
	printf("malloc: \n");
	test_malloc(array, total_size);
	printf("\nmm_malloc: \n");
	test_mm_malloc(array, total_size);
	
	return 0;
}
	
/* output: (TIMES = 7500)
malloc: 
run time(seconds): 0.002583
malloc size(bytes): 2530491, heap size: 2568192

mm_malloc: 
run time(seconds): 0.020037
malloc size(bytes): 2530491, heap size: 2588672
*/

/* output: (TIMES = 75000, 需要修改memlib.c的MAX_HEAP为200MB)
malloc: 
run time(seconds): 0.016412
malloc size(bytes): 24969908, heap size: 25681920

mm_malloc: 
run time(seconds): 3.428341
malloc size(bytes): 24969908, heap size: 25559040
*/

// mm_malloc和C库malloc空间利用率差距不大
// mm_malloc运行时间和为C库malloc的差距随内存分配的个数成指数增长
