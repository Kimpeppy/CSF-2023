/* Hexdump main function, assembly language version */

	.section .text

	.globl main
main:
	/* TODO: add your code here */

	.globl hex_to_printable
	hex_to_printable:
		cmpb $31, %dil // Check if the byteval is greater than 31
		ja .greater // Jump if it's greater
		jmp .less // Jump if it's less
	.greater:
		movb %dil, %al // Move the arguement into the return register
		ret
	.less:
		movb $46, %dil // Make dil a period before returning it
		movb %dil, %al // Move the arguement into the return register
	ret

/* vim:ft=gas:
 */
