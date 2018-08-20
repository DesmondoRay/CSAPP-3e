/* slow ersion */

/* version 0: 4.3s */
void transpose_0(int *dst, int *src, int dim)
{
	int i, j;
	
	for (i = 0; i < dim; i++) {
		int addr = i * dim;
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[addr + j];
	}
}

/* version 1: 4.7s */
void transpose_1(int **dst, int **src, int dim)
{
	int i, j;
	
	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++)
			dst[j][i] = src[i][j];
	}
}
/* 测试 version 1 */
void test_1_1(void)
{
	int i, j;
	// 为dest分配内存
	int **(dest) = (int **) malloc(N * sizeof(int*));
	for (i = 0; i < N; i++)
		dest[i] = (int *) malloc(N * sizeof(int)); 
	// 为source分配内存,并初始化
	int **(source) = (int **) malloc(N * sizeof(int*));
	for (i = 0; i < N; i++) {
		source[i] = (int *) malloc(N * sizeof(int)); 
		int num = i % 2;
		for (j = 0; j < N; j++)
			source[i][j] = num;
	}
	
	// 测试 version 1
	clock_t start;
	clock_t end;
	start = clock();
	transpose_1(dest, source, N);
	end = clock();
	printf("run time: %lf\n", difftime(end, start)/CLOCKS_PER_SEC);
	
	// 释放dest, source内存
	for (i = 0; i < N; i++) {
		free(dest[i]);
		free(source[i]);
	}
	free(dest);
	free(source);
}

/* version 2: 3.8s */
void transpose_2(int *dst, int *src, int dim)
{
	int i, j;
	
	for (i = 0; i < dim; i++) {
		int addr = i*dim;
		for (j = 0; j < dim; j+=2) {
			dst[j*dim +i] = src[addr + j];
			dst[j*dim + (i+dim)] = src[addr + (j+1)];
		}
	}
}

/* version 3: 2.5s*/
void transpose_3(int *dst, int *src, int dim)
{
	int i, j;
	
	for (i = 0; i < dim; i+=2) {
		int addr1 = i*dim;
		int addr2 = (i+1)*dim;
		for (j = 0; j < dim; j++) {
			dst[j*dim + i] = src[addr1 + j];
			dst[j*dim + (i+1)] = src[addr2 + j];
		}
	}
}

/* version 4: 1.3s*/
void transpose_4(int *dst, int *src, int dim)
{
	int i, j;
	int limit = dim - 4;
	
	for (i = 0; i < limit; i+=4) {
		int addr0 = i*dim;
		int addr1= (i+1)*dim;
		int addr2= (i+2)*dim;
		int addr3= (i+3)*dim;
		for (j = 0; j < dim; j++) {
			dst[j*dim + i] = src[addr0 + j];
			dst[j*dim + (i+1)] = src[addr1 + j];
			dst[j*dim + (i+2)] = src[addr2 + j];
			dst[j*dim + (i+3)] = src[addr3 + j];
		}
	}
	
	for (; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim + j];
}

/* version 5: 1.1s*/
void transpose_5(int *dst, int *src, int dim)
{
	int i, j;
	int limit = dim - 8;
	
	for (i = 0; i < limit; i+=8) {
		int addr0 = i*dim;
		int addr1= (i+1)*dim;
		int addr2= (i+2)*dim;
		int addr3= (i+3)*dim;
		int addr4= (i+4)*dim;
		int addr5= (i+5)*dim;
		int addr6= (i+6)*dim;
		int addr7= (i+7)*dim;
		for (j = 0; j < dim; j++) {
			int addr_j = j*dim;
			dst[addr_j + i] = src[addr0 + j];
			dst[addr_j + (i+1)] = src[addr1 + j];
			dst[addr_j + (i+2)] = src[addr2 + j];
			dst[addr_j + (i+3)] = src[addr3 + j];
			dst[addr_j + (i+4)] = src[addr4 + j];
			dst[addr_j + (i+5)] = src[addr5 + j];
			dst[addr_j + (i+6)] = src[addr6 + j];
			dst[addr_j + (i+7)] = src[addr7 + j];
		}
	}
	
	for (; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim + j];
}

/* version 6: 0.96s*/
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
			dst[addr_j + (i+1)] = src[addr1 + j];
			dst[addr_j + (i+2)] = src[addr2 + j];
			dst[addr_j + (i+3)] = src[addr3 + j];
			dst[addr_j + (i+4)] = src[addr4 + j];
			dst[addr_j + (i+5)] = src[addr5 + j];
			dst[addr_j + (i+6)] = src[addr6 + j];
			dst[addr_j + (i+7)] = src[addr7 + j];
			dst[addr_j + (i+8)] = src[addr8 + j];
			dst[addr_j + (i+9)] = src[addr9 + j];
			dst[addr_j + (i+10)] = src[addr10 + j];
			dst[addr_j + (i+11)] = src[addr11 + j];
			dst[addr_j + (i+12)] = src[addr12 + j];
			dst[addr_j + (i+13)] = src[addr13 + j];
			dst[addr_j + (i+14)] = src[addr14 + j];
			dst[addr_j + (i+15)] = src[addr15 + j];
		}
	}
	
	for (; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim + j];
}

/* version 7: 0.99s*/
void transpose_7(int *dst, int *src, int dim)
{
	int i, j;
	int limit = dim - 32;
	
	for (i = 0; i < limit; i+=32) {
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
		int addr16= (i+16)*dim;
		int addr17= (i+17)*dim;
		int addr18= (i+18)*dim;
		int addr19= (i+19)*dim;
		int addr20= (i+20)*dim;
		int addr21= (i+21)*dim;
		int addr22= (i+22)*dim;
		int addr23= (i+23)*dim;
		int addr24= (i+24)*dim;
		int addr25= (i+25)*dim;
		int addr26= (i+26)*dim;
		int addr27= (i+27)*dim;
		int addr28= (i+28)*dim;
		int addr29= (i+29)*dim;
		int addr30= (i+30)*dim;
		int addr31= (i+31)*dim;
		for (j = 0; j < dim; j++) {
			int addr_j = j*dim;
			dst[addr_j + i] = src[addr0 + j];
			dst[addr_j + (i+1)] = src[addr1 + j];
			dst[addr_j + (i+2)] = src[addr2 + j];
			dst[addr_j + (i+3)] = src[addr3 + j];
			dst[addr_j + (i+4)] = src[addr4 + j];
			dst[addr_j + (i+5)] = src[addr5 + j];
			dst[addr_j + (i+6)] = src[addr6 + j];
			dst[addr_j + (i+7)] = src[addr7 + j];
			dst[addr_j + (i+8)] = src[addr8 + j];
			dst[addr_j + (i+9)] = src[addr9 + j];
			dst[addr_j + (i+10)] = src[addr10 + j];
			dst[addr_j + (i+11)] = src[addr11 + j];
			dst[addr_j + (i+12)] = src[addr12 + j];
			dst[addr_j + (i+13)] = src[addr13 + j];
			dst[addr_j + (i+14)] = src[addr14 + j];
			dst[addr_j + (i+15)] = src[addr15 + j];
			dst[addr_j + (i+16)] = src[addr16 + j];
			dst[addr_j + (i+17)] = src[addr17 + j];
			dst[addr_j + (i+18)] = src[addr18 + j];
			dst[addr_j + (i+19)] = src[addr19 + j];
			dst[addr_j + (i+20)] = src[addr20 + j];
			dst[addr_j + (i+21)] = src[addr21 + j];
			dst[addr_j + (i+22)] = src[addr22 + j];
			dst[addr_j + (i+23)] = src[addr23 + j];
			dst[addr_j + (i+24)] = src[addr24 + j];
			dst[addr_j + (i+25)] = src[addr25 + j];
			dst[addr_j + (i+26)] = src[addr26 + j];
			dst[addr_j + (i+27)] = src[addr27 + j];
			dst[addr_j + (i+28)] = src[addr28 + j];
			dst[addr_j + (i+29)] = src[addr29 + j];
			dst[addr_j + (i+30)] = src[addr30 + j];
			dst[addr_j + (i+31)] = src[addr31 + j];
		}
	}
	
	for (; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[j*dim + i] = src[i*dim + j];
}