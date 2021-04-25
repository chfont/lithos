#ifndef gdt_h
#define gdt_h
#include <stdint.h>

typedef struct gdt_entry {
  uint16_t limit;
  uint16_t base;
  uint8_t base_8_bits;
  uint8_t access_byte;
  uint8_t limit_flag;
  uint8_t base_continued;
} __attribute__((packed)) gdt_entry;

// Struct Explanation:
/*
  Due to backwards compatibility:
  GDT Entry is 8 bytes. first 2 are the first 2 bytes of limit, a 20 bit value
  Next is the start of base, a 32bit address.

  for i386+, this is followed by: 8 bits of base, an access byte, the last 4
  bits of limit + 4 bits for flags, and the remainder of the base.
 */

typedef struct gdtr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdtr_t;

#endif
