#ifndef vga_info_h
#define vga_info_h
#include <stddef.h>
#include <stdint.h>

enum vga_color {
  VGA_BLACK = 0,
  VGA_BLUE = 1,
  VGA_GREEN = 2,
  VGA_CYAN = 3,
  VGA_RED = 4,
  VGA_MAGENTA = 5,
  VGA_BROWN = 6,
  VGA_LIGHT_GRAY = 7,
  VGA_GRAY = 8,
  VGA_LIGHT_BLUE = 9,
  VGA_LIGHT_GREEN = 10,
  VGA_LIGHT_CYAN = 11,
  VGA_LIGHT_RED = 12,
  VGA_LIGHT_MAGENTA = 13,
  VGA_YELLOW = 14,
  VGA_WHITE = 15
};

typedef enum vga_color vga_color;
inline unsigned char vga_info(uint8_t fg, uint8_t bg) { return fg | bg << 4; }
inline unsigned short vga_char(unsigned char c, uint8_t color) { return c | color << 8; }

typedef struct terminal {
  uint16_t* terminal_buffer;
  uint32_t row;
  uint32_t column;
  const uint32_t height;
  const uint32_t width;
  uint8_t foreground_color;
  uint8_t background_color;
} terminal;

void init_term(terminal* term);
void write(terminal* term, const char* s, size_t size);
void set_foreground(terminal* term, vga_color color);
void set_background(terminal* term, vga_color color);

#endif
