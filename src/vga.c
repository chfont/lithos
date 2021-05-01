#include "vga.h"

terminal term = {.terminal_buffer = (uint16_t*)0xB8000,
                 .row = 0,
                 .column = 0,
                 .height = 30,
                 .width = 80,
                 .foreground_color = VGA_WHITE,
                 .background_color = VGA_BLACK};

// Initialization only intended to be used with constant terminal declared above
// Only one terminal object can exist, as there is one vga buffer currently
void init_term(terminal* term) {
  for (uint32_t i = 0; i < term->height; i++) {
    for (uint32_t j = 0; j < term->width; j++) {
      int q = i * term->width + j;
      term->terminal_buffer[q] = vga_char(' ', vga_info(VGA_WHITE, VGA_BLACK));
    }
  }
}


void terminal_write_char(terminal* term, char c){
  uint64_t index = term->row * term->width + term->column;
  switch (c){
  case '\n':
    term->column = 0;
        if (++(term->row) == term->height) {
          term->row = 0;
        }
        break;
  case '\b':
        if (term->column == 0) {
          term->column = term->width - 1;
          if (term->row != 0) {
            term->row--;
          }
        } else {
          term->column--;
        }
        break;
  default:
    term->terminal_buffer[index] =
    vga_char(c, vga_info(term->foreground_color, term->background_color));
    if (++(term->column) == term->width) {
      term->column = 0;
      if (++(term->row) == term->height) {
	term->row = 0;
      }
    }
  }
}

void terminal_write(terminal* term, const char* s, size_t size) {
  for (unsigned int i = 0; i < size; i++) {
    terminal_write_char(term, s[i]);
  }
}

void set_foreground(terminal* term, vga_color color) { term->foreground_color = color; }

void set_background(terminal* term, vga_color color) { term->background_color = color; }
