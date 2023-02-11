/* Assembly language implementation of hexdump functions */

	.section .rodata

	/* TODO: add read-only data such as strings here */

	.section .text

	/* TODO: add functions here */
	.globl hex_read
	hex_read:

	.globl hex_write_string
	hex_write_string:

	.globl hex_format_offset
	hex_format_offset:

	.globl hex_format_byte_as_hex
	hex_format_byte_as_hex:
	// first variable is r8b and second is sil
		movb %sil, %r8b // move first argument into a temp register/r8b
		shrb $4, %r8b
		andb $15, %sil
		cmpb $10, %r8b
		ja .hexLess
		jmp .hexGreater
	.hexLess:
		addb $48, %r8b
	.hexGreater:


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
