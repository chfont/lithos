
ENTRY(_start)

SECTIONS {
	 . = 1M;
	 .boot : {
	  KEEP(*(.mboot))
	 }
	 .text : {
	    *(.text)
	 }
	 .rodata : ALIGN(4K) {
	  *(.rodata)
	 }
	 .data : ALIGN(4K){
	  *(.data)
	  }
	 .bss : ALIGN(4K) {
	  *(COMMON)
	  *(.bss)
	 }
}
