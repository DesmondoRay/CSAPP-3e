/*
 * 家庭作业3.61
 */
 
#include <stdio.h>
#include <assert.h>

long cread_alt(long *xp) {
    return (!xp ? 0 : *xp);
}

long cread(long *xp) {
    return (xp ? *xp : 0);
}

int main(void)
{
    long a = 2;
    long *p = NULL;
    
    assert(cread(p) == cread_alt(p));
    assert(cread(&a) == cread_alt(&a));
    return 0;
}