	global setup_gdt:function
setup_gdt:;_setup_gdt(gdtr_t* gdtr) is the signature
	cli
	mov eax, [esp +4]
	lgdt [eax]
	jmp 0x08:cleanup	
cleanup:
	mov eax, 0x10
	mov ds, eax
	mov ss, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	ret
