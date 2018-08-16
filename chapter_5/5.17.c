/**
 * homework 5.17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* Basic implementation of memset */
void *memset_8x1(void *s, int c, size_t n)
{
    size_t K = sizeof(unsigned long);
    size_t cnt = 0;
    unsigned char *schar = s;
    
    // 对齐
    while((cnt < n) && (size_t)schar % K != 0) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    
    // 生成c_K，包含K个c
    size_t shift = 8;
    unsigned long c_K = c;
    for(size_t shift = 1; shift < K; shift*=2) {
        c_K = (c_K << shift*8) + c_K;
    }
    
    // 一次装下K个c
    unsigned long *long_K = (unsigned long*)schar;
    size_t limit = n - cnt - K;
    for(; cnt < limit; cnt+=K) {
        *long_K++ = c_K;
    }
    
    // 处理剩下的几个c
    schar = (unsigned char*) long_K;
    for(; cnt < n; cnt++){
        *schar++ = (unsigned char) c;
    }
    return s;
}

int main(void)
{
    int c = 0xff;
    size_t n = 424239;
    void *s1 = (void*) malloc(n*sizeof(long));
    void *s2 = (void*) malloc(n*sizeof(long));
    memset_8x1(s1, c, n);
    // 使用库函数测试
    memset(s2, c, n);
    
    if (memcmp(s1, s2, n) == 0)
        printf("test ok.\n");
    
    free(s1);
    free(s2);
    return 0;
}