	extern int_h:function

%macro INTR 1
	global int%1:function
int%1:
	cli
	push 0
	push %1
	jmp int_stub
%endmacro

%macro INTRE 1
	global int%1:function

int%1:
	cli
	push %1
	jmp int_stub
%endmacro

int_stub:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	call int_h
	pop eax
	mov ds, ax
	mov ss, ax
	mov es, ax
	popa
	add esp, 8; esp point to return, not pushed args
	sti
	ret
	

	INTR 0
	INTR 1
	INTR 2
	INTR 3
	INTR 4
	INTR 5
	INTR 6
	INTR 7
	INTRE 8
	INTR 9
	INTRE 10
	INTRE 11
	INTRE 12
	INTRE 13
	INTRE 14
	INTR 15
	INTR 16
	INTR 17
	INTR 18
	INTR 19
	INTR 20
	INTR 21
	INTR 22
	INTR 23
	INTR 24
	INTR 25
	INTR 26
	INTR 27
	INTR 28
	INTR 29
	INTR 30
	INTR 31
		
	global set_idtr:function
set_idtr:
	mov eax, [esp+4]
	lidt [eax]
	ret
	
	global enable_interrupts:function
enable_interrupts:		;Stub to reenable interrupts after idt is setup
	sti
	ret
