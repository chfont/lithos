#ifndef itoa_h
#define itoa_h
#include <stddef.h>
#include <stdbool.h>

//Implementation of itoa(), a common non-ANSI function for turning integers to strings, to use internally
int itoa(int32_t val, char* buf, int base){
  if (base < 2 || base > 16){ return -1;}
  bool negative = val < 0;
  char internal_buf[10]; //Need at most 10 digits
  size_t digits_used = 0;
  while(val != 0){
    internal_buf[digits_used++] = "0123456789abcdef"[val % base];
    val /= 10;
  }
  // internal_buf holds the string backwards, so we need to reverse it
  int index = negative? 1 : 0;
  if (negative){
    buf[0] = '-';
  }
  while(digits_used){
    buf[index++] = internal_buf[digits_used-1];
    digits_used--;
  }
  return 0;
}

#endif
