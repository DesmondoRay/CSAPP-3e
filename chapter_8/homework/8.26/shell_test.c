/* 
 * homework 8.26
 *
 * 测试函数: 根据命令行参数指定休眠秒数，若未指定则，只休眠一秒
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int num, i;
	
	if (argc == 1)
		num = 1;
	else if (argc == 2)
		num = atoi(argv[1]);
	
	for (i = 0; i < num; i++)
		sleep(1);
	
	return 0;
}