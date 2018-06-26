/*
	编写calloc的实现，通过调用malloc执行分配，调用memset将内存设置为0.
	保证没有任何算术溢出引起的漏洞，且无论数据类型size_t用多少位表示，
	代码都应该正常工作。
	相关函数声明如下：
		void *calloc(size_t nmemb, size_t size);
		void *malloc(size_t size);
		void *memset(void *s, int c, size_t n);
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

void *calloc(size_t nmemb, size_t size)
{
	if (nmemb == 0 || size == 0)
		return NULL;
	
	size_t bytes = nmemb * size;
	if (nmemb == bytes / size)
	{
		void* ptr = malloc(bytes);
		memset(ptr, 0, bytes);
		return ptr;
	}
	
	return NULL;
}

int main(void) 
{
  void* p;
  p = calloc(0x1234, 1);
  assert(p != NULL);
  free(p);

  p = calloc(SIZE_MAX, 2);
  assert(p == NULL);
  free(p);
  
  return 0;
}