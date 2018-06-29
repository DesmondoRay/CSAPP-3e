/*
 * 家庭作业3.71
 *
 * 写一个函数good_echo，从标准输入读取一行，再把它写到标准输出。函数的实现应该
 * 对任意长度的输入行都能工作。可以使用库函数fgets，但是必须确保即使当输入行
 * 要求比已经为缓冲区分配的更多的空间时，函数也能正确的工作。
 * 还应该检查错误条件，要在遇到错误条件时返回。
 */
 
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 20

int good_echo(void);
 
int main(void)
{
    good_echo();
    return 0;
}

int good_echo(void)
{
    char s[BUF_SIZE];
    char *p;
    
    while(1) {
        p = fgets(s, sizeof(s)-1, stdin);
        if (p == NULL) {
            return 0;
            break;
        }
        printf("%s", s);
    }
    return 1;
}