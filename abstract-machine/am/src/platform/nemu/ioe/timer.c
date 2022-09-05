#include <am.h>
#include <nemu.h>
#include <riscv/riscv.h>

uint32_t sys_usec, sys_sec;

void __am_timer_init() {
  sys_usec = *(uint32_t *)RTC_ADDR;
  sys_sec = *(uint32_t *)(RTC_ADDR + 4);
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t low  = *(uint32_t*)(RTC_ADDR + 0); 
  uint32_t high = *(uint32_t*)(RTC_ADDR + 4);
  uptime->us = ((uint64_t)high - sys_sec) * 1000000 + low - sys_usec + 500;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
