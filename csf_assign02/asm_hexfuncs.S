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
		// r10d is the index tracking on the array
		// rsi is the array that stores the char array
		// edi stores the offset as a char variable
		// r11b is a temp variable to store the remainder
		movl $0, %r10d
	.setAllToZero:
		cmpl $8, %r10d
		jge .beginFunction

		movb $48, (%rsi, %r10, 1)
		incl %r10d
		jmp .setAllToZero
	
	.beginFunction:
		movl $8, %r10d // Make the r10 register the index we are on, which is 8/ where the null terminator will be
		movb $0, (%rsi, %r10, 1) // Set the null terminator at the end of the char array
		decl %r10d // Decrement the index by 1
		cmpl $0, %r10d 
		ja .offsetLoopOne // Jump to first loop if greater than 0
		ret
	.offsetLoopOne:
		movq $0, %r11
		movb %dil, %r11b // Move the current offset into a temp register to use and operation
		andb $15, %r11b // Get the remainder
		cmpb $10, %r11b // Compare the remainder to 0
		jb .loopOneLess // Jump to assigning num to array
		jmp .loopOneGreater // Jump to assigning letter to array
	.loopOneLess:
		addb $48, %r11b // Add 48 to make it a number
		movb %r11b, (%rsi, %r10, 1) // Move the character into the array
		jmp .offsetLoopTwo // Jump to the end of the loop
	.loopOneGreater:
		addb $87, %r11b // Add 48 to make it a letter
		movb %r11b, (%rsi, %r10, 1) // Move the character into the array
	.offsetLoopTwo:
		shrl $4, %edi // Shift the offset by 4 to the right
		decl %r10d // Decrement the index by 1
		cmpl $0, %r10d // Compare the offset to 0
		jge .offsetLoopOne
		ret



	.globl hex_format_byte_as_hex
	hex_format_byte_as_hex:
	// first variable is r8b and second is dil
		movl $2, %r10d
		movb $0, (%rsi, %r10, 1)
		movb %dil, %r8b // move first argument into a temp register/r8b
		movl $0, %r10d // store first index of the array register as 0 in r10d 
		shrb $4, %r8b // shift the first argument by 4 bytes
		andb $15, %dil // find remainder
		cmpb $10, %r8b // check if the first argument/value in r8b is less than 10
		jb .hexLess // jump if it's less
		jmp .hexGreater // jump if it's greater
	.hexLess:
		addb $48, %r8b // add 48 to the first hex digit
		movb %r8b, (%rsi, %r10, 1) //move the value into the array register
		incl %r10d // increment the index of the array register
		jmp .hexTwo // jump to the second if statement
	.hexGreater:
		addb $87, %r8b // add 87 to the first hex digit
		movb %r8b, (%rsi, %r10, 1)//move the argument into the array register
		incl %r10d // increment the index of the array register
	
	.hexTwo: // second function call for the second argument/hex digit
		cmpb $10, %dil // check if the second argument/value in dil is less than 10
		jb .hexLessTwo // jump if it's less
		jmp .hexGreaterTwo // jump if it's greater
	.hexLessTwo:
		addb $48, %dil // add 48 to the second hex digit
		movb %dil, (%rsi, %r10, 1) // move the argument into the array register to return
		ret
	.hexGreaterTwo:
		addb $87, %dil // add 87 to the second hex digit
		movb %dil, (%rsi, %r10, 1) // move the argument into the array register to return
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
