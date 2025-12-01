	.file	"bubble_sorts.c"
	.text
	.p2align 4
	.globl	compare_int
	.type	compare_int, @function
compare_int:
.LFB33:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	subl	(%rsi), %eax
	ret
	.cfi_endproc
.LFE33:
	.size	compare_int, .-compare_int
	.p2align 4
	.globl	bubble_basic
	.type	bubble_basic, @function
bubble_basic:
.LFB29:
	.cfi_startproc
	endbr64
	leal	-1(%rsi), %edx
	testl	%edx, %edx
	jle	.L3
	leaq	4(%rdi), %r9
	.p2align 4,,10
	.p2align 3
.L5:
	subl	$1, %edx
	movq	%rdi, %rax
	movq	%rdx, %r8
	leaq	(%r9,%rdx,4), %rsi
	.p2align 4,,10
	.p2align 3
.L7:
	movl	(%rax), %edx
	movl	4(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L6
	movl	%ecx, (%rax)
	movl	%edx, 4(%rax)
.L6:
	addq	$4, %rax
	cmpq	%rsi, %rax
	jne	.L7
	movl	%r8d, %edx
	testl	%r8d, %r8d
	jne	.L5
.L3:
	ret
	.cfi_endproc
.LFE29:
	.size	bubble_basic, .-bubble_basic
	.p2align 4
	.globl	bubble_early_stop
	.type	bubble_early_stop, @function
bubble_early_stop:
.LFB30:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leal	-1(%rsi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	testl	%ebp, %ebp
	jle	.L12
	movl	%esi, %ebx
	movq	%rdi, %r9
	movl	%ebp, %r10d
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L25:
	xorl	%edx, %edx
	xorl	%r11d, %r11d
	.p2align 4,,10
	.p2align 3
.L13:
	movslq	%edx, %rax
	salq	$2, %rax
	leaq	(%r9,%rax), %rdi
	leaq	4(%r9,%rax), %rax
	movl	(%rdi), %ecx
	movl	(%rax), %r8d
	cmpl	%r8d, %ecx
	jle	.L14
	addl	$1, %edx
	movl	%r8d, (%rdi)
	movl	$1, %r11d
	movl	%ecx, (%rax)
	cmpl	%edx, %r10d
	jg	.L13
.L16:
	addl	$1, %esi
	cmpl	%ebp, %esi
	jge	.L12
	movl	%ebx, %r10d
	subl	%esi, %r10d
	subl	$1, %r10d
	testl	%r10d, %r10d
	jg	.L25
.L12:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_restore_state
	addl	$1, %edx
	cmpl	%r10d, %edx
	jl	.L13
	testl	%r11d, %r11d
	jne	.L16
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE30:
	.size	bubble_early_stop, .-bubble_early_stop
	.p2align 4
	.globl	bubble_branchless
	.type	bubble_branchless, @function
bubble_branchless:
.LFB31:
	.cfi_startproc
	endbr64
	leal	-1(%rsi), %edx
	testl	%edx, %edx
	jle	.L27
	leaq	4(%rdi), %r10
	.p2align 4,,10
	.p2align 3
.L29:
	subl	$1, %edx
	movq	%rdi, %rax
	movq	%rdx, %r9
	leaq	(%r10,%rdx,4), %r8
	.p2align 4,,10
	.p2align 3
.L30:
	movl	(%rax), %edx
	movl	4(%rax), %ecx
	cmpl	%ecx, %edx
	movl	%ecx, %esi
	cmovle	%edx, %esi
	cmovl	%ecx, %edx
	addq	$4, %rax
	movl	%esi, -4(%rax)
	movl	%edx, (%rax)
	cmpq	%rax, %r8
	jne	.L30
	movl	%r9d, %edx
	testl	%r9d, %r9d
	jne	.L29
.L27:
	ret
	.cfi_endproc
.LFE31:
	.size	bubble_branchless, .-bubble_branchless
	.p2align 4
	.globl	bubble_cocktail
	.type	bubble_cocktail, @function
bubble_cocktail:
.LFB32:
	.cfi_startproc
	endbr64
	leal	-1(%rsi), %r8d
	testl	%r8d, %r8d
	jle	.L54
	movslq	%r8d, %rax
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rdi, %rcx
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leaq	-4(%rdi,%rax,4), %rdx
	leal	-3(%rsi), %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L41:
	movl	%ebx, %ebp
	movq	%rbx, %rax
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L38:
	movl	(%rcx,%rax,4), %esi
	movl	4(%rcx,%rax,4), %edi
	cmpl	%edi, %esi
	jle	.L37
	movl	%edi, (%rcx,%rax,4)
	movl	$1, %r9d
	movl	%esi, 4(%rcx,%rax,4)
.L37:
	addq	$1, %rax
	cmpl	%eax, %r8d
	jg	.L38
	subl	$1, %r8d
	testl	%r9d, %r9d
	je	.L35
	cmpl	%ebx, %r8d
	jle	.L35
	leaq	-4(%rdx), %rax
	movl	%r12d, %esi
	xorl	%r11d, %r11d
	salq	$2, %rsi
	movq	%rax, %r10
	movq	%rax, %r13
	subq	%rsi, %r10
	jmp	.L40
	.p2align 4,,10
	.p2align 3
.L57:
	subq	$4, %rax
.L40:
	movl	(%rdx), %esi
	movl	-4(%rdx), %edi
	cmpl	%edi, %esi
	jge	.L39
	movl	%edi, (%rdx)
	movl	%r9d, %r11d
	movl	%esi, -4(%rdx)
.L39:
	movq	%rax, %rdx
	cmpq	%rax, %r10
	jne	.L57
	addl	$1, %ebp
	addq	$1, %rbx
	subl	$2, %r12d
	cmpl	%ebp, %r8d
	jle	.L35
	andl	$1, %r11d
	je	.L35
	movq	%r13, %rdx
	jmp	.L41
	.p2align 4,,10
	.p2align 3
.L35:
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L54:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	ret
	.cfi_endproc
.LFE32:
	.size	bubble_cocktail, .-bubble_cocktail
	.p2align 4
	.globl	standard_qsort
	.type	standard_qsort, @function
standard_qsort:
.LFB34:
	.cfi_startproc
	endbr64
	movslq	%esi, %rsi
	leaq	compare_int(%rip), %rcx
	movl	$4, %edx
	jmp	qsort@PLT
	.cfi_endproc
.LFE34:
	.size	standard_qsort, .-standard_qsort
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
