/**
 * homework 12.34
 */

#include "csapp.h"
#define M 1000
#define N 1000

long **mul_matrix1(long **a, long **b);
long **mul_matrix2(long **a, long **b);
long **mul_matrix3(long **a, long **b);
void *mul_thread(void *vargp);
void print_result(long **matrix);

long nelems_per_thread;
int thread_index;
sem_t mutex;

struct matrix_ptrs {
	long ** result;
	long ** a;
	long ** b;
};

int main(void)
{
	long **a = (long **) Malloc(M*sizeof(long*));
	long **b = (long **) Malloc(N*sizeof(long*));
	int i, j;
	for (i = 0; i < N; i++)
		b[i] = (long *) Malloc(M*sizeof(long));
	for (i = 0; i < M; i++) {
		a[i] = (long *) Malloc(M*sizeof(long));
		for (j = 0; j < N; j++) {
			a[i][j] = i+j+1;
			b[j][i] = i+j+1;
		}
	}
	
	/* 使用clock()计算多线程运行时间会得到错误结果；如：
	 * nthreads = 2, runtime = 8..
	 * nthreads = 4, runtime = 16..
	 * 而test_run_time.c程序中，runtime = 0.000498 
	clock_t start = clock();
	long **c = mul_matrix3(a, b);
	clock_t end = clock();
	printf("run time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
	*/
	struct timeval start, end;
	gettimeofday(&start, NULL);
	long **c = mul_matrix3(a, b);
	gettimeofday(&end, NULL);
	double runtime = end.tv_sec - start.tv_sec + 
		(double)(end.tv_usec - start.tv_usec)/1000000;
	printf("run time: %f\n", runtime);
	//print_result(c);
	return 0;
}

/* run time: 17.5s */
long **mul_matrix1(long **a, long **b)
{
	int i, j, k;
	long **result = (long **) Malloc(M*sizeof(long *));
	
	for (i = 0; i < M; i++) {
		result[i] = (long *) Malloc(M*sizeof(long));
		for (j = 0; j < M; j++) {
			result[i][j] = 0;
			for (k = 0; k < N; k++) {
				result[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	
	return result;
}

/* run time: 11.5s */
long **mul_matrix2(long **a, long **b)
{
	int i, j, k;
	long **result = (long **) Malloc(M*sizeof(long *));
	
	for (i = 0; i < M; i++) {
		result[i] = (long *) Malloc(M*sizeof(long));
		for (j = 0; j < M; j++) {
			long temp_sum = 0;
			for (k = 0; k < N; k++) {
				temp_sum += a[i][k]*b[k][j];
			}
			result[i][j] = temp_sum;
		}
	}
	
	return result;
}

/* run time: 5.9s (nthreads = 2) */
/* run time: 5.6s (nthreads = 4) */
/* run time: 5.2s (nthreads = 8) */
long **mul_matrix3(long **a, long **b)
{
	int i;
	int nthreads = 8;
	long **result = (long **) Malloc(M*sizeof(long *));
	pthread_t tid[nthreads];
	
	nelems_per_thread = M/nthreads;
	sem_init(&mutex, 0, 1);
	
	struct matrix_ptrs args;
	args.result = result;
	args.a = a;
	args.b = b;
	for (i = 0; i < nthreads; i++) {
		Pthread_create(&tid[i], NULL, mul_thread, (void *)&args);
	}
	for (i = 0; i < nthreads; i++)
		Pthread_join(tid[i], NULL);
	
	return result;
}

void *mul_thread(void *vargp)
{
	int i, j, k;
	long start;
	
	P(&mutex);
	start = thread_index * nelems_per_thread;
	thread_index++;
	V(&mutex);
	
	struct matrix_ptrs *temp;
	temp = (struct matrix_ptrs *) vargp;
	long **result = temp->result;
	long **a = temp->a;
	long **b = temp->b;
	long end = start + nelems_per_thread;
	
	for (i = start; i < end; i++) {
		result[i] = (long *) Malloc(M*sizeof(long));
		for (j = 0; j < M; j++) {
			long temp_sum = 0;
			for (k = 0; k < N; k++) {
				temp_sum += a[i][k]*b[k][j];
			}
			result[i][j] = temp_sum;
		}
	}
}
	
void print_result(long **matrix)
{
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++)
			printf("%ld\t", matrix[i][j]);
		printf("\n");
	}
	return;
}