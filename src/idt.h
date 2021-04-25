#ifndef idt_h
#define idt_h
#include <stddef.h>
#include <stdint.h>

// structures for idt implementation
typedef struct idtr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idtr_t;

typedef struct idt_entry {
  uint16_t addr_low;
  uint16_t segment_selector;
  uint8_t zero_byte;  // 5 reserved bytes, 3 guaranteed 0;
  uint8_t flag;
  uint16_t addr_high;
} __attribute__((packed)) idt_entry;

void init_idt_entry(idt_entry* entry, uint32_t addr, uint16_t segment, uint8_t flag);
int init_idt_entries(idt_entry* entries, size_t count);

#endif
