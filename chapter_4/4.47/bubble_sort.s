	.file	"bubble_sort.c"
	.text
	.globl	bubble_sort
	.type	bubble_sort, @function
bubble_sort:
.LFB24:
	.cfi_startproc
	jmp	.L2
.L4:
	movq	8(%rax), %rdx
	movq	(%rax), %rcx
	cmpq	%rcx, %rdx
	jge	.L3
	movq	%rcx, 8(%rax)
	movq	%rdx, (%rax)
.L3:
	addq	$8, %rax
	jmp	.L5
.L6:
	movq	%rdi, %rax
.L5:
	cmpq	%rsi, %rax
	jb	.L4
	subq	$8, %rsi
.L2:
	cmpq	%rdi, %rsi
	ja	.L6
	rep ret
	.cfi_endproc
.LFE24:
	.size	bubble_sort, .-bubble_sort
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$48, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	$3, (%rsp)
	movq	$1, 8(%rsp)
	movq	$4, 16(%rsp)
	movq	$2, 24(%rsp)
	leaq	24(%rsp), %rsi
	movq	%rsp, %rdi
	call	bubble_sort
	movl	$0, %ebx
	jmp	.L8
.L9:
	movq	(%rsp,%rbx,8), %rdx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	addq	$1, %rbx
.L8:
	cmpq	$3, %rbx
	jbe	.L9
	movl	$0, %eax
	movq	40(%rsp), %rcx
	xorq	%fs:40, %rcx
	je	.L10
	call	__stack_chk_fail
.L10:
	addq	$48, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
