/*
 * 家庭作业3.73
 *
 * 用汇编代码写出匹配图3-51中函数find_range行为的函数。
 * 代码必须只包含一个浮点比较指令，并用条件分支指令来生成正确的结果。
 */

// ubuntu 16.04测试成功

#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x) {
  	__asm__(
      	"vxorps %xmm1, %xmm1, %xmm1\n\t"
      	"vucomiss %xmm1, %xmm0\n\t"
      	"jp .P\n\t"
      	"ja .A\n\t"
     	"jb .B\n\t"
      	"je .E\n\t"
      	".A:\n\t"
     	"movl $2, %eax\n\t"
      	"jmp .Done\n\t"
      	".B:\n\t"
      	"movl $0, %eax\n\t"
      	"jmp .Done\n\t"
      	".E:\n\t"
      	"movl $1, %eax\n\t"
      	"jmp .Done\n\t"
      	".P:\n\t"
      	"movl $3, %eax\n\t"
      	".Done:\n\t"
	);
}

int main(void) {
	puts("start tests");
  	assert(OTHER == find_range(NAN));
  	assert(NEG == find_range(-2.3));
  	assert(ZERO == find_range(0.0));
  	assert(POS == find_range(3.33));
	puts("done!");
  	return 0;
}