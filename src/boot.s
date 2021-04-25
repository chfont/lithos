	_ALIGN equ 1
        MEMINFO equ 1 << 1 	;provide memory map
	FLAGS equ _ALIGN | MEMINFO
	MAGIC equ 0x1BADB002
	CHECKSUM equ -(MAGIC + FLAGS)

	section .boot
	align 4
mboot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	
;; Define stack, as multiboot will not
	section .bss
	align 16
stack_bottom:
	resb 16384 		; 16kb stack
stack_top:

	section .text
	global _start:function
_start:
	mov esp, stack_top
	extern kernel_main 	; declare kernel main to be linked in later
	call kernel_main 	;main function of kernel code
	cli
halt:
	hlt
	jmp halt
end:	
