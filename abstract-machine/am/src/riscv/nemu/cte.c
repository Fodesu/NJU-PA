#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>
#define  Machine_external_interrupt (11)
static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  c->mepc = c->mepc + 4;
  if (user_handler) {
    Event ev = {0};
    switch (c->mstatus) {
      case 11 :
        ev.event = EVENT_SYSCALL;
        break;
      case -1 :
        ev.event = EVENT_YIELD;
      default: 
        ev.event = EVENT_ERROR; 
        break;
    }
    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  // 异常入口地址 = 0， 初始化状态寄存器 mtvec = 0;
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  // a7 = -1(uint32_t) = gpr(17)
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
