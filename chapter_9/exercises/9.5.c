/**
 * exercise 9.5
 */

#include "../code/csapp.h"

void mmapcopy(int fd, int size)
{
	char *bufp;
	
	bufp = Mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	Write(1, bufp, size);
	return;
}

int main(int argc, char *argv[]) 
{
	int fd;
	struct stat stat;
	if (argc < 2) {
		fprintf(stderr, "Need at least 2 command line arguments.\n");
		exit(1);
	}
	
	fd = Open(argv[1], O_RDONLY, 0);
	
	fstat(fd, &stat);
	mmapcopy(fd, stat.st_size);
	
	return 0;
}