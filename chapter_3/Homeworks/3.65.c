/*
 * 家庭作业3.65
 *
 * A. A[i][j] in %rdx;
 * B. A[j][i] in %rax;
 * C. M = 15
 */
 
#define M 15

void transpose(long A[M][M]) {
    long i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < i; j++) {
            long t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
        
}