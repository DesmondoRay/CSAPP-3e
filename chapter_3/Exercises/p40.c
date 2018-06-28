/*
 * 练习题3.40
 */

#define N 16
typedef int fix_matrix[N][N];

void fix_set_diag_opt(fix_matrix A, int val)
{
	int *ptr = &A[0][0];
	int *end = &A[N][N];
	do {
		*ptr = val;
		ptr += N + 1;
	} while (ptr != end);
	return;
}