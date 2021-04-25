# Lithos
Lithos is a work-in-progress 32-bit kernel, targetting x86 processors. It is meant primarily as a hobby project, to get more hands on knowledge of operating system and kernel internals, and to apply my knowledge to something I find interesting.

## Building

In order to build Lithos, a cross-compiler targetting i686 is needed. On many Linux distributions, a package containing this may exist, under a name such as `i686-elf-gcc`. For the x86 assembly code necessary for the lowest level components, `nasm` is needed. With these two tools, the code is compilable into a final binary. A makefile is provided to automate the process using `make`. 

If the cross compiler mentioned is not available, `clang` can build the object files, with the target triple `i686-none-elf`, but a cross-linker is then necessary, as clang will use the system linker by default, rather than targetting the proper target.

## Running

Testing the kernel has so far been done using `Qemu`, an open source machine emulator. Once installed, running `qemu-system-i686 -kernel lithos.bin` will launch the emulator, booting into the compiled kernel.

## Status:

Code for writing to the VGA buffer, with 16 colors, is present.

The GDT and IDT are initialized, though the interrupts present are only the 32 processor interrupts needed to prevent crashing. These are stubs currently.
