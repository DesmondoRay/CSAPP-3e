/*
 * 家庭作业3.60
 *
 * A. x in %rdi, n in %esi, result in %rax, mask in %rdx;
 * B. 初始值: result = 0, mask = 1;
 * C. mask != 0;
 * D. mask = mask << (n & 0xFF);
 * E. (mask&x) in %r8, result = result | %r8;
 */
 
long loop(long x, int n)
{
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << (n & 0xFF)) {
        result |= mask&x;
    }
    return result;
}
