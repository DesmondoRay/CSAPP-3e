/*
	写一个函数，将整数val复制到缓冲区buf中，但是只有当缓冲区由足够可用的空间时，
		才执行复制。
 */
 
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void copy_int(int val, void *buf, int maxbytes)
{
	if (maxbytes - (int) sizeof(val) >= 0)
		memcpy(buf, (void *) &val, sizeof(val));
}

int main(void)
{
	int maxbytes = sizeof(int) * 10;
	void* buf = malloc(maxbytes);
	int val;

	val = 0x12345678;
	copy_int(val, buf, maxbytes);
	assert(*(int*)buf == val);

	val = 0xAABBCCDD;
	copy_int(val, buf, 0);
	assert(*(int*)buf != val);
	
	free(buf);
	return 0;
}