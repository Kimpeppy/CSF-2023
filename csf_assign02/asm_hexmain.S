/* Hexdump main function, assembly language version */

	.section .text

	.globl main
main:
	/* TODO: add your code here */

	.globl helper_call_format_as_hex
	helper_call_format_as_hex:
		// temp variable to store index for space array
		movq $0, %r10
		// first element in space array is a (literal) space
		movb $32, (%r12, %r10, 1)
		incl %r10d // increment space array index
		// second element in the space array is the null terminator
		movb $0, (%r12, %r10, 1)
		jmp .checkLoop

	.formatByte: 
		movq (), %rdi
		call hex_format_byte_as_hex
		movq %rsi, $rdi
		call hex_write_string

		call hex_to_printable
		movq %r12, %rdi
		call hex_write_string

	.checkLoop:
		// check 
		cmpb $48, %rdx
		jX .formatByte


	 

/* vim:ft=gas:
 */
