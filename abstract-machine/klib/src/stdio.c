#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
#include<stdio.h>

void putostr(char* out, const char* s) {
  strcat(out, s);
}

void pchar(char* out, char c) {
  size_t len = strlen(out);
  out[len] = c;
  out[len + 1] = '\0'; 
}

void pits(char* out, const int dec) {
    putostr(out, itoa(dec));
}

void putint(const int dec) {
  putstr(itoa(dec));
}

// void putfloat(const float flt) {
//   int tmpint = (int)flt;  
//   int tmpflt = (int)(100000 * (flt - tmpint));  
//   if(tmpflt % 10 >= 5) {  
//       tmpflt = tmpflt / 10 + 1;  
//   }  
//   else {  
//       tmpflt = tmpflt / 10;  
//   }  
//   putint(tmpint);  
//   putch('.');
//   putint(tmpflt);
// }


int vprintf(const char *fmt, va_list param) {
  int cnt = 0;
  while(*fmt) {
    if(*fmt != '%') {
      putch(*fmt);
      fmt++;
      cnt++;
    } else {
      fmt++;
      switch(*fmt) {
        case 'c': case 'C': {
          char valch = va_arg(param, int);
          putch(valch);
          fmt++;
          break;
        }
        case 'D': case 'd': {
          int valint = va_arg(param, int);
          putint(valint);
          fmt++;
          break;
        }
        // case 'f': {
        //   float valfloat = va_arg(param, double);
        //   putfloat(valfloat);
        //   fmt++;
        //   break;
        // }
        case 's': {
          char *valstr = va_arg(param, char*);
          putstr(valstr);
          fmt++;
          break;
        }
        default : {
          putch(*fmt);
          fmt++;
        }
      }
    }
  }
  return cnt;
}

int printf(const char *fmt, ...) {
  int n;
  va_list list;
  va_start(list, fmt);
  n = vprintf(fmt, list);
  va_end(list);
  return n;
}

int vsprintf(char *str, const char *format, va_list ap) {
  int cnt = 0;
  while(*format) {
  if(*format != '%') {
    pchar(str, *format);
    format++;
  } else {
    cnt++; 
    format++;
    switch(*format) {
      case 'c': case 'C': {
        char valch = va_arg(ap, int);
        pchar(str, valch);
        format++;
        break;
      }
      case 'D': case 'd': {
        int valint = va_arg(ap, int);
        pits(str, valint);
        format++;
        break;
      }
      case 's': {
        char *valstr = va_arg(ap, char*);
        putostr(str, valstr);
        format++;
        break;
      }
      default :
        putch(*format);
        format++;
      }
    }
  }
  return cnt;
}

int sprintf(char *out, const char *fmt, ...) {
  int ret = 0;
  va_list args;
  va_start(args, fmt);
  ret = vsprintf(out, fmt, args);
  va_end(args);
  return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  int ret = 0;
  va_list args;
  va_start(args, fmt);
  ret = vsnprintf(out, n, fmt, args);
  va_end(args);
  return ret;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  size_t cnt = 0;
  while(*fmt && cnt < n) {
    if(*fmt != '%') {
      pchar(out, *fmt);
      fmt++;
    } else {
        cnt++;
        fmt++;
      switch(*fmt) {
        case 'c': case 'C': {
          char valch = va_arg(ap, int);
          pchar(out, valch);
          fmt++;
          break;
        }
        case 'D': case 'd': {
          int valint = va_arg(ap, int);
          pits(out, valint);
          fmt++;
          break;
        }
        case 's': {
          char *valstr = va_arg(ap, char*);
          putostr(out, valstr);
          fmt++;
          break;
        }
        default :
          putch(*fmt);
          fmt++;
        }
      }
    }
  return cnt;
}

#endif
