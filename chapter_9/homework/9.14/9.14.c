/**
 * homework 9.14
 *
 * 使用mmap将hello.txt的内容改变为"Jello, world!\n"。
 */

#include "../../code/csapp.h"

int main(void)
{
	int fd;
	struct stat st;
	char *bufp;
	
	fd = Open("hello.txt", O_RDWR, 0);
	fstat(fd, &st);
	
	bufp = Mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
	*bufp = 'J';
	
	Write(1, bufp, st.st_size);
	Munmap(bufp, st.st_size);
	
	exit(0);
}
