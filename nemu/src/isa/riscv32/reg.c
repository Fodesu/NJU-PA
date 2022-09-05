#include <isa.h>
#include "local-include/reg.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  // for(int i = 0; i < 32; i++) {
  //   printf("%s is %d    %x\n", reg_name(i, 0), gpr(i), gpr(i));
  // }
  int length = ARRLEN(regs);
  int i = 0;
  printf("=========寄存器信息=========\n");
  for (i = 0; i < length; i+= 4){
    for (int j = i; j < MIN(length, i + 4); ++j){
      printf("\e[1;36m%3s:\e[0m %#12x | ", regs[j], cpu.gpr[j]._32);
    }
    printf("\n");
  }
}

word_t isa_reg_str2val(const char *s, bool *success) {
  // printf("%s in the isa_reg_str2val\n", s);
  for(int i = 0; i < 32; i++) {
    if(strcmp(regs[i], s) == 0) {
      return gpr(i);
    }
  }
  const char* pc = "pc";
  if(strcmp(s, pc) == 0) return cpu.pc;
  *success = false;
  if(*success == false) Log("Bad ret_to_val");
  return 0;
}

const char* paddtoname(const rtlreg_t* preg) {
  return regs[check_reg_idx(preg - &gpr(0))];
}