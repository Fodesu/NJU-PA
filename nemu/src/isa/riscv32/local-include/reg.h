#ifndef __RISCV32_REG_H__
#define __RISCV32_REG_H__

#include <common.h>

const char* paddtoname(const rtlreg_t* preg);

static inline int check_reg_idx(int idx) {
  IFDEF(CONFIG_RT_CHECK, Assert(idx >= 0 && idx < 32, "out of the range of reg"));
  return idx;
}

#define gpr(idx) (cpu.gpr[check_reg_idx(idx)]._32)

static inline const char* reg_name(int idx, int width) {
  extern const char* regs[];
  return regs[check_reg_idx(idx)];
}

#endif
