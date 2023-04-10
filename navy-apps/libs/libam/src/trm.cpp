#include <am.h>
#include <unistd.h>
#include <assert.h>

#define out 1
Area heap;

static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  _exit(code);
  // should not reach here
  while (1);
}
