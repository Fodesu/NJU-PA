#ifndef __AM_H__
#define __AM_H__

#define ARCH_H "navy.h"
#include "am-origin.h"

#define  DEVICE_BASE 0xa0000000
#define  MMIO_BASE   0xa0000000
#define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
#define FB_ADDR         (MMIO_BASE   + 0x1000000)
#define SYNC_ADDR       (VGACTL_ADDR + 4)
#define SIZE_ADDR       (VGACTL_ADDR)
#define SERIAL_PORT     (DEVICE_BASE + 0x00003f8)

#if defined(__ISA_X86__)
# define nemu_trap(code) asm volatile (".byte 0xd6" : :"a"(code))
#elif defined(__ISA_MIPS32__)
# define nemu_trap(code) asm volatile ("move $v0, %0; .word 0xf0000000" : :"r"(code))
#elif defined(__ISA_RISCV32__) || defined(__ISA_RISCV64__)
# define nemu_trap(code) asm volatile("mv a0, %0; .word 0x0000006b" : :"r"(code))
#else
#endif

#if defined(__ARCH_X86_NEMU)
# define DEVICE_BASE 0x0
#else
# define DEVICE_BASE 0xa0000000
#endif

#define MMIO_BASE 0xa0000000

#endif
