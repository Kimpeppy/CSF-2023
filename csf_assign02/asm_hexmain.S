/* Hexdump main function, assembly language version */

	.section .rodata
space: .string " "
colon: .string ":" 
newLine: .string "\n"

	.section .data
data_buf: .string "0000000000000000"
sbuf: .string "00000000"

	.section .text

	.globl main
main:
		push %r12  // register for storing data_buf elements which have memory allocated on stack
		push %r13  // register for storing sbuf elements which have memory allocated on stack
		subq $8, %rsp  // stack pointer alignment

		movq $data_buf, %r12
		movq $sbuf, %r13
		movl $16, %r10d // Make the r10 register the index 16, where the null terminator will be
		movb $0, (%r12, %r10, 1) // Set the null terminator at the end of the char data_buf array
		movl $0, %r11d  // starting index of the data_buf char array
		jmp .checkFirstLoop

	.setDataBufToZero:
		movb $48, (%r12, %r11, 1)  // set all entries in data_buf to store 0
		incl %r11d // increment current index of data_buf array
	.checkFirstLoop:
		cmpl $16, %r11d  // check if index is less than 16
		jl .setDataBufToZero  // if it is, set next entry in the array to 0

		movl $0, %r11d  // starting index of the sbuf char array
		jmp .checkSecondLoop
	
	.setSbufToZero:
		movb $48, (%r13, %r11, 1)  // set all entries sbuf to store 0
		incl %r11d  // increment current index of sbuf array
	.checkSecondLoop:
		cmpl $8, %r11d  // check if index is less than 8
		jl .setSbufToZero  // if it is, set next entry in the array to 0

		movq %r12, %rdi  // pass data_buf as first argument to hex_read
		call hex_read 
		movq %rax, %rdx  // store value returned in temp variable 
		// stored temp in rdx because it will be the third argument for helper_call_format_as_hex later on
		movb $0, (%r12, %rdx, 1) // set null terminator at index returned by hex_read
		movl $0, %r10d  // counter variable to keep track of offset
		jmp .checkWhileLoopCondition

	.startWhileLoop:
		movq %r10, %rdi  // store/pass counter value as first argument
		movq %r13, %rsi  // store/pass sbuf array as second argument
		call hex_format_offset
		movq %r13, %rdi  // store/pass sbuf array as first argument
		call hex_write_string
		movq $colon, %rdi  // store/pass colon character as first argument
		call hex_write_string
		movq $space, %rdi  // store/pass space character as first argument
		call hex_write_string
		movq %r12, %rdi   // store/pass data_buf as first argument
		movq %r13, %rsi   // store/pass sbuf as second argument
		call helper_call_format_as_hex
		movq %r12, %rdi   // store/pass data_buf as first argument
		call hex_write_string
		movq $newLine, %rdi  // store/pass newline character as first argument
		call hex_write_string
		movq %r12, %rdi  // store/pass data_buf as first argument
		call hex_read
		movq %rax, %rdx  // store new value returned by read in temp
		movb $0, (%r12, %rdx, 1)  // set data_buf entry at temp to null terminator
		addl $16, %r10d  // increment counter by 16

	.checkWhileLoopCondition:
		cmpq $0, %rdx  // check whether value of temp variable is equal to 0 or not
		jne .startWhileLoop  // keep looping if it is not

		addq $8, %rsp  // restore stack alignment
		pop %r13  // pop sbuf first because last element added to the stack is at the top (LIFO)
		pop %r12  // now pop data_buf
		ret


	.globl helper_call_format_as_hex
	helper_call_format_as_hex:
		push %r12
		subq $16, %rsp
		movl $0, %eax
		movq $0, %r12   // variable for indexing of loop
		jmp .checkFirstLoopCondition

	.startFirstLoop: 
		movb (%rdi, %r10, 1), %r11b   // r11b stores data_buf[i]
		movq %r11, %rdi   // move data_buf[i] to rdi as first argument to hex_format_byte_as_hex
		call hex_format_byte_as_hex
		movq %rsi, %rdi    // move sbuf[] to rdi as first argument for hex_write_string
		call hex_write_string
		movq %r11, %rdi   // move data_buf[i] to first argument register again
		call hex_to_printable
		movl %eax, %r11d   // store the value returned into data_buf[i]
		movq $space, %rdi   // space is passed as argument to hex_write_string
		call hex_write_string
		incq %r12   // increment current index
	.checkFirstLoopCondition:
		// check if condition of for loop is being met i.e., whether i < temp
		// rdx stores temp since it is the third argument of the function
		cmpq %r10, %rdx    // check if i is less than temp
		jb .startFirstLoop  // go to loop if it is less

		movq %rdx, %r12    // i points to the same value as temp
		jmp .checkSecondLoopCondition
	
	.startSecondLoop:
		movq $space, %rdi    // make space char the argument for next 3 consecutive function calls
		call hex_write_string
		movq $space, %rdi
		call hex_write_string
		movq $space, %rdi
		call hex_write_string
		incq %r12   // increment index i by 1
	.checkSecondLoopCondition:
		cmpq $16, %r12    // check if i is less than 16
		jb .startSecondLoop // if i is less/16 is greater than i

		movq $space, %rdi    // for last function call to hex_write_string
		call hex_write_string
		addq $16, %rsp
		pop %r12
		ret


/* vim:ft=gas:
 */
