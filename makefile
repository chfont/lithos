FLAGS = -ffreestanding -g -O2 -Wall
NASM_FLAGS = -g -felf32

lithos.bin: kernel.o boot.o vga.o gdt.o idt.o interrupts.o
	i686-elf-gcc -T link.ld -o lithos.bin $(FLAGS) -nostdlib kernel.o boot.o vga.o gdt.o idt.o interrupts.o
kernel.o: src/kernel.c src/idt.c
	i686-elf-gcc -c src/kernel.c src/idt.c $(FLAGS)
vga.o: src/vga.c 
	i686-elf-gcc -c src/vga.c -o vga.o $(FLAGS)
boot.o: src/boot.s
	nasm $(NASM_FLAGS) -o boot.o src/boot.s
gdt.o: src/gdt.s
	nasm $(NASM_FLAGS) -o gdt.o src/gdt.s
interrupts.o: src/interrupts.s
	nasm $(NASM_FLAGS) -o interrupts.o src/interrupts.s