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

	// first variable is r8b and second is dil
		movb %dil, %r8b // move first argument into a temp register/r8b
		movl $0, %r10d // 
		shrb $4, %r8b
		andb $15, %dil
		cmpb $10, %r8b
		jb .hexLess
		jmp .hexGreater
	.hexLess:
		addb $48, %r8b
		movb %r8b, (%rsi, %r10, 1)
		incl %r10d
		jmp .hexTwo
	.hexGreater:
		addb $87, %r8b
		movb %r8b, (%rsi, %r10, 1)
		incl %r10d
	
	.hexTwo:
		cmpb $10, %dil
		jb .hexLessTwo
		jmp .hexGreaterTwo
	.hexLessTwo:
		addb $48, %dil
		movb %dil, (%rsi, %r10, 1)
		ret
	.hexGreaterTwo:
		addb $87, %dil
		movb %dil, (%rsi, %r10, 1)
		ret


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
