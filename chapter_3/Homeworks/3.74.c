/*
 * 家庭作业3.74
 *
 * 用汇编代码写出匹配图3-51中函数find_range行为的函数。
 * 代码必须只包含一个浮点比较指令，并用条件传送指令来生成正确的结果。
 * 使用指令cmovp，如果设置了偶校验位传送。
 */

// ubuntu 16.04测试成功

#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x) {
  	__asm__(
      	"vxorps %xmm1, %xmm1, %xmm1\n\t"
      	"movq $1, %rax\n\t"
      	"movq $2, %r8\n\t"
      	"movq $0, %r9\n\t"
      	"movq $3, %r10\n\t"
      	"vucomiss %xmm1, %xmm0\n\t"
      	"cmovaq %r8, %rax\n\t"
      	"cmovbq %r9, %rax\n\t"
      	"cmovpq %r10, %rax\n\t"  // cmovpq指令需要放在最后比较
	);
}

int main(void) {
	puts("start test");
  	assert(OTHER == find_range(NAN));
  	assert(NEG == find_range(-2.3));
  	assert(ZERO == find_range(0.0));
  	assert(POS == find_range(3.33));
	puts("done!");
  	return 0;
}