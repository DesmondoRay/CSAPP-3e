/**
 * homework 6.45
 *
 * 转置一个类型为int的N*N的矩阵，设计一个运行得尽可能快的转置函数。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 15000

/* 原版: 4.1s */
void transpose(int *dst, int *src, int dim)
{
	int i, j;
	
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim + j];
}

/* 
 * version 6: 0.96s; 
 * 估算每转置一个元素需要21个有效周期, 测试机器有效周期时间为0.2ns
 */
void transpose_6(int *dst, int *src, int dim)
{
	int i, j;
	int limit = dim - 16;
	
	for (i = 0; i < limit; i+=16) {
		int addr0 = i*dim;
		int addr1= (i+1)*dim;
		int addr2= (i+2)*dim;
		int addr3= (i+3)*dim;
		int addr4= (i+4)*dim;
		int addr5= (i+5)*dim;
		int addr6= (i+6)*dim;
		int addr7= (i+7)*dim;
		int addr8= (i+8)*dim;
		int addr9= (i+9)*dim;
		int addr10= (i+10)*dim;
		int addr11= (i+11)*dim;
		int addr12= (i+12)*dim;
		int addr13= (i+13)*dim;
		int addr14= (i+14)*dim;
		int addr15= (i+15)*dim;
		for (j = 0; j < dim; j++) {
			int addr_j = j*dim;
			dst[addr_j + i] = src[addr0 + j];
			dst[addr_j + i+1] = src[addr1 + j];
			dst[addr_j + i+2] = src[addr2 + j];
			dst[addr_j + i+3] = src[addr3 + j];
			dst[addr_j + i+4] = src[addr4 + j];
			dst[addr_j + i+5] = src[addr5 + j];
			dst[addr_j + i+6] = src[addr6 + j];
			dst[addr_j + i+7] = src[addr7 + j];
			dst[addr_j + i+8] = src[addr8 + j];
			dst[addr_j + i+9] = src[addr9 + j];
			dst[addr_j + i+10] = src[addr10 + j];
			dst[addr_j + i+11] = src[addr11 + j];
			dst[addr_j + i+12] = src[addr12 + j];
			dst[addr_j + i+13] = src[addr13 + j];
			dst[addr_j + i+14] = src[addr14 + j];
			dst[addr_j + i+15] = src[addr15 + j];
		}
	}
	
	for (; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim + j];
}

/* 测试 */
void test_transpose(void)
{
	int i, j;
	// 为dest分配内存
	int *dest = (int *) malloc(N * N * sizeof(int));
	// 为source分配内存,并初始化
	int *source = (int *) malloc(N * N * sizeof(int));
	for (i = 0; i < N; i++) {
		int num = i % 2;
		for (j = 0; j < N; j++)
			source[i*N + j] = num;
	}
	
	clock_t start;
	clock_t end;
	start = clock();
	transpose_6(dest, source, N);
	end = clock();
	printf("run time: %lf\n", difftime(end, start)/CLOCKS_PER_SEC);
	
	// 释放dest, source内存
	free(dest);
	free(source);
}

int main(void)
{
	test_transpose();
	return 0;
}