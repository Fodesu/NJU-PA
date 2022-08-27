#ifndef __RTL_PSEUDO_H__
#define __RTL_PSEUDO_H__

#ifndef __RTL_RTL_H__
#error "Should be only included by <rtl/rtl.h>"
#endif

/* RTL pseudo instructions */

static inline def_rtl(li, rtlreg_t* dest, const rtlreg_t imm) {
  rtl_addi(s, dest, rz, imm);
}

static inline def_rtl(mv, rtlreg_t* dest, const rtlreg_t *src1) {
  rtl_addi(s, dest, src1, 0);
}

static inline def_rtl(not, rtlreg_t *dest, const rtlreg_t* src1) {
  // dest <- ~src1
  rtl_xori(s, dest, src1, -1);
}

static inline def_rtl(neg, rtlreg_t *dest, const rtlreg_t* src1) {
  // dest <- -src1
  // 取反加一 
  rtl_xori(s, dest, src1, -1);
  rtl_addi(s, dest, rz, 1);
}

static inline def_rtl(sext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- signext(src1[(width * 8 - 1) .. 0])
  switch(width) {
    case 1:
      *dest = (int32_t)(int8_t)*src1;
      break;
    case 2:
      *dest = (int32_t)(int16_t)*src1;
      break;
    case 4:
      *dest = (int32_t)*src1;
      break;
    default:
      panic("unexcepted with: %d", width);
  }
}

static inline def_rtl(zext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- zeroext(src1[(width * 8 - 1) .. 0])
  switch(width) {
    case 1:
      *dest = (uint32_t)(uint8_t)*src1;
      break;
    case 2:
      *dest = (uint32_t)(uint16_t)*src1;
      break;
    case 4: 
      *dest = (uint32_t)*src1;
    default:
      panic("unexcepted with: %d", width);
  }
}

static inline def_rtl(msb, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- src1[width * 8 - 1]
  *dest = *src1 >> (width * 8 - 1);
}
#endif
