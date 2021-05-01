#include "idt.h"
#include <stddef.h>
#include "vga.h"
#include "itoa.h"
#include "strlen.h"
extern uint32_t int0;
extern uint32_t int1;
extern uint32_t int2;
extern uint32_t int3;
extern uint32_t int4;
extern uint32_t int5;
extern uint32_t int6;
extern uint32_t int7;
extern uint32_t int8;
extern uint32_t int9;
extern uint32_t int10;
extern uint32_t int11;
extern uint32_t int12;
extern uint32_t int13;
extern uint32_t int14;
extern uint32_t int15;
extern uint32_t int16;
extern uint32_t int17;
extern uint32_t int18;
extern uint32_t int19;
extern uint32_t int20;
extern uint32_t int21;
extern uint32_t int22;
extern uint32_t int23;
extern uint32_t int24;
extern uint32_t int25;
extern uint32_t int26;
extern uint32_t int27;
extern uint32_t int28;
extern uint32_t int29;
extern uint32_t int30;
extern uint32_t int31;

void init_idt_entry(idt_entry* entry, uint32_t addr, uint16_t segment, uint8_t flag) {
  entry->addr_low = addr & 0xFFFF;
  entry->addr_high = (addr >> 16) & 0xFFFF;
  entry->segment_selector = segment;
  entry->flag = flag;
  entry->zero_byte = 0;
}

// Return -1 if not initialized, 0 otherwise
int init_idt_entries(idt_entry* entries, size_t count) {
  if (count < 32) {
    return -1;
  }
  uint32_t handlers[32] = {int0,  int1,  int2,  int3,  int4,  int5,  int6,  int7,
                           int8,  int9,  int10, int11, int12, int13, int14, int15,
                           int16, int17, int18, int19, int20, int21, int22, int23,
                           int24, int25, int26, int27, int28, int29, int30, int31};
  for (int i = 0; i < 32; i++) {
    init_idt_entry(&(entries[i]), handlers[i], 0x08, 0x8E);
  }
  return 0;
}

extern terminal term;

void int_h(register_state state) {
  uint8_t color = term.foreground_color;
  set_foreground(&term, VGA_RED);
  write(&term, "Received Interrupt: ", 20);
  char buf[10] = {0};
  if(itoa(state.interrupt_number, buf, 10)){
    write(&term, "Invalid Interrupt Number\n", 26); //Sanity check, should never occur
  } else {
    int i = strlen(buf);
    write(&term, buf, strlen(buf));
    write(&term, "\n", 1);
  }
  set_foreground(&term, color);
}
