/*
 * 家庭作业3.64
 *
 * A. &A[i][j][k] = x_A + L(S*T*i + T*j + k)
      其中x_A为数组A的起始位置, L=sizeof(long);
 * B. R = 7, S = 5, T = 13;
 */

#define R 7
#define S 5
#define T 13

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}