#include <stdbool.h>

#include "gdt.h"
#include "idt.h"
#include "vga.h"
// Global terminal data
extern terminal term;

// GDT structure functions, from assembly
extern void setup_gdt(gdtr_t* gdtr);
extern void set_idtr(idtr_t*);
extern void enable_interrupts();
extern void int3();  // TODO: Remove Once interrupt code finalized.

void init_gdt_entry(gdt_entry* entry, uint32_t limit, uint32_t base, uint8_t access,
                    bool block_granularity, bool _32bit);

void kernel_main() {
  gdt_entry entries[5];  // null, code, data
  init_gdt_entry(&(entries[0]), 0, 0, 0, false, false);
  init_gdt_entry(&(entries[1]), 0xffffffff, 0, 0x9A, true, true);
  init_gdt_entry(&(entries[2]), 0xffffffff, 0, 0x92, true, true);
  // user-mode code
  init_gdt_entry(&(entries[3]), 0xffffffff, 0, 0xFA, true, true);
  // user-mode data
  init_gdt_entry(&(entries[4]), 0xffffffff, 0, 0xF2, true, true);

  gdtr_t gdtr = {.limit = sizeof(gdt_entry) * 5 - 1, .base = (uint32_t)(entries)};
  setup_gdt(&gdtr);

  // Setup IDT
  idt_entry idt_entries[32];
  int err = init_idt_entries(idt_entries, 32);
  idtr_t idtr = {.limit = sizeof(idt_entry) * 32 - 1, .base = (uint32_t)(idt_entries)};
  set_idtr(&idtr);

  init_term(&term);
  set_foreground(&term, VGA_LIGHT_GREEN);
  enable_interrupts();
  int3();
  write(&term, "Welcome To Lithos:", 18);
}

void init_gdt_entry(gdt_entry* entry, uint32_t limit, uint32_t base, uint8_t access,
                    bool block_granularity, bool _32bit) {
  if (limit >= 1 << 20) {
    limit = limit >> 12;  // limit is a 20 bit value
  }
  entry->base = base & 0xFFFF;
  entry->limit = limit & 0xFFFF;
  entry->base_8_bits = (base >> 16) & 0xFF;
  entry->access_byte = access;
  entry->base_continued = (base >> 24) & 0xFF;

  uint8_t flag = (limit >> 16) & 0x0F;
  if (block_granularity) {
    flag |= 0x80;
  }
  if (_32bit) {
    flag |= 0x40;
  }
  entry->limit_flag = flag;
}
