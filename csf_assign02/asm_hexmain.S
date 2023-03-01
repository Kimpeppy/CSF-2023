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
		push %r12  // memory allocated on stack for data_buf
		push %r13  // memory allocated on stack for sbuf
		push %r14  // store counter value on stack
		push %rbx  // store value for temp variable
		subq $8, %rsp  // stack pointer alignment

		movq $data_buf, %r12 // store/copy elements of data_buf in r12
		movq $sbuf, %r13    // store/copy elements of sbuf in r13
		movl $16, %r10d // r10 stores index 16, where the null terminator will be
		movb $0, (%r12, %r10, 1) // set null terminator at the end of data_buf array

		movq %r12, %rdi  // pass data_buf as first argument
		call hex_read 
		movq %rax, %rbx  // store value returned in temp variable
		movb $0, (%r12, %rbx, 1) // set null terminator at index returned by hex_read
		movq $0, %r14   // counter starts at 0 to keep track of offset
		jmp .checkWhileLoopCondition

	.startWhileLoop:
		movq %r14, %rdi  // pass counter value as first argument
		movq %r13, %rsi  // pass sbuf array as second argument
		call hex_format_offset
		movq %r13, %rdi  // pass sbuf array as first argument
		call hex_write_string
		movq $colon, %rdi  // pass colon character as first argument
		call hex_write_string
		movq $space, %rdi  // pass space character as first argument
		call hex_write_string
		movq %r12, %rdi   // pass data_buf as first argument
		movq %r13, %rsi   // pass sbuf as second argument
		movq %rbx, %rdx   // pass temp as third argument
		call helper_call_format_as_hex
		movq %r12, %rdi   // pass data_buf as first argument
		call hex_write_string
		movq $newLine, %rdi  // pass newline character as first argument
		call hex_write_string
		movq %r12, %rdi  // pass data_buf as first argument
		call hex_read
		movq %rax, %rbx  // store new value returned by read in temp
		movb $0, (%r12, %rbx, 1)  // set data_buf at temp to null terminator
		addq $16, %r14  // increment counter by 16

	.checkWhileLoopCondition:
		cmpq $0, %rbx   // check whether temp is equal to 0
		jne .startWhileLoop  // keep looping if it is not

		addq $8, %rsp  // restore stack alignment
		pop %rbx  // pop temp val
		pop %r14  // pop counter val
		pop %r13  // pop sbuf first because LIFO
		pop %r12  // pop data_buf
		ret


	.globl helper_call_format_as_hex
	helper_call_format_as_hex:
		push %r12 // memory allocated on stack for storing data_buf
		push %r13 // memory allocated on stack for storing sbuf
		push %r14 // store/save counter value
		push %r15 // stores value of data_buf[i]
		push %rbx // store/save value of temp variable on stack
	
		movq %rdi, %r12 // store/copy elements of data_buf in r12
		movq %rsi, %r13 // store/copy elements of sbuf in r13
		movq $0, %r14  // save counter starting at 0
		movq %rdx, %rbx  // save temp in rbx
		jmp .checkFirstLoopCondition

	.startFirstLoop: 
		movq (%r12, %r14, 1), %r15   // r15 stores data_buf[i]
		movq %r15, %rdi   // move data_buf[i] to rdi as first argument
		movq %r13, %rsi   // move sbuf to rsi as second argument
		call hex_format_byte_as_hex
		movq %r13, %rdi  // move sbuf[] to rdi as first argument
		call hex_write_string
		movq %r15, %rdi   // move data_buf[i] to first argument register again
		call hex_to_printable
		movb %al, (%r12, %r14, 1)  // store the value returned into data_buf[i]
		movq $space, %rdi   // space is passed as argument to hex_write_string
		call hex_write_string
		incq %r14   // increment current index
	.checkFirstLoopCondition:
		cmpq %rbx, %r14    // check if i is less than temp
		jb .startFirstLoop  // go to loop if it is less

		movq %rbx, %r14   // i points to/stores the same value as temp
		jmp .checkSecondLoopCondition
	
	.startSecondLoop:
		movq $space, %rdi  // make space char argument for next 3 function calls
		call hex_write_string
		movq $space, %rdi
		call hex_write_string
		movq $space, %rdi
		call hex_write_string
		incq %r14   // increment index i by 1
	.checkSecondLoopCondition:
		cmpq $16, %r14    // check if i is less than 16
		jb .startSecondLoop // if i is less/16 is greater than i

		movq $space, %rdi  // first argument for last function call
		call hex_write_string
		pop %rbx  // pop temp first
		pop %r15  // pop data_buf[i] pointer val
		pop %r14  // pop counter
		pop %r13  // pop sbuf
		pop %r12  // pop data_buf
		ret


/* vim:ft=gas:
 */
