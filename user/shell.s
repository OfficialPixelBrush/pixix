	.file	"shell.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"pixix"
.LC1:
	.string	"Failed to set hostname!\n"
.LC2:
	.string	"# "
.LC3:
	.string	"FAILURE\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x70,0x6
	.cfi_escape 0x10,0x7,0x2,0x75,0x7c
	.cfi_escape 0x10,0x6,0x2,0x75,0x78
	.cfi_escape 0x10,0x3,0x2,0x75,0x74
	subl	$416, %esp
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	movl	%gs:20, %eax
	movl	%eax, -28(%ebp)
	xorl	%eax, %eax
	pushl	$5
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	%eax
	call	sethostname@PLT
	addl	$16, %esp
	testl	%eax, %eax
	je	.L2
	pushl	%esi
	pushl	$24
	leal	.LC1@GOTOFF(%ebx), %eax
	pushl	%eax
	pushl	$1
	call	write@PLT
	addl	$16, %esp
.L2:
	leal	.LC2@GOTOFF(%ebx), %esi
.L11:
	pushl	%ecx
	pushl	$2
	pushl	%esi
	pushl	$1
	call	write@PLT
	addl	$12, %esp
	pushl	$256
	leal	-284(%ebp), %edi
	pushl	%edi
	pushl	$0
	call	read@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jle	.L10
	cmpb	$10, -285(%ebp,%eax)
	jne	.L4
	movb	$0, -285(%ebp,%eax)
	jmp	.L5
.L4:
	movb	$0, -284(%ebp,%eax)
.L5:
	call	fork@PLT
	testl	%eax, %eax
	js	.L10
	jne	.L6
	movl	%edi, -412(%ebp)
	movl	%edi, %eax
	movl	$1, %ecx
.L7:
	movb	(%eax), %dl
	testb	%dl, %dl
	je	.L18
	incl	%eax
	cmpb	$32, %dl
	jne	.L7
	movb	$0, -1(%eax)
	movl	%eax, -412(%ebp,%ecx,4)
	incl	%ecx
	jmp	.L7
.L18:
	xorl	%eax, %eax
	movl	%eax, -412(%ebp,%ecx,4)
	pushl	%edx
	pushl	$0
	leal	-412(%ebp), %eax
	pushl	%eax
	pushl	%edi
	call	execve@PLT
	addl	$12, %esp
	pushl	$8
	leal	.LC3@GOTOFF(%ebx), %eax
	pushl	%eax
	pushl	$1
	call	write@PLT
	addl	$16, %esp
	jmp	.L10
.L6:
	pushl	$4
	leal	-412(%ebp), %eax
	pushl	%eax
	pushl	$0
	pushl	$0
	call	waitid@PLT
	addl	$16, %esp
	jmp	.L11
.L10:
	subl	$12, %esp
	pushl	$0
	call	_exit@PLT
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB13:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE13:
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
