#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t min(size_t a, size_t b) {
  return a <= b ? a : b;
}

size_t strlen(const char *s) {
  assert(s != NULL);
  size_t len = 0;
  while(s[len] != '\0') {
    len++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  assert(dst != NULL);
  assert(src != NULL);
  size_t i = 0;
  for(i = 0; src[i] != '\0'; i++) {
    dst[i] = src[i];
  }
  dst[i] = src[i];
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  assert(src != NULL && dst != NULL);
  size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++)
      dst[i] = src[i];
  for ( ; i < n; i++)
      dst[i] = '\0';

  return dst;
}

char *strcat(char *dst, const char *src) {
  assert(src != NULL && dst != NULL);
  size_t  dst_len = strlen(dst);
  size_t i;
  for(i = 0; src[i] != '\0'; i++) {
    dst[dst_len + i] = src[i];
  }
  dst[dst_len + i] = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  assert(s1 != NULL && s2 != NULL);
  size_t len1 = strlen(s1), len2 = strlen(s2);
  for(int i = 0; i < min(len1, len2); i++) {
    if(s1[i] > s2[i]) return 1;
    else if(s2[i] > s1[i]) return -1;
  }
  if(len1 > len2) return 1;
  else if(len2 > len1) return -1;
  return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  assert(s1 != NULL);
  if(!n) 
    return 0;
  while(--n && *s1 && *s1 == *s2) {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

void *memset(void *s, int c, size_t n) {
  assert(s != NULL);
  char* p = (char*)s;
  for(size_t i = 0; i < n; i++) {
    *p = c;
    p++;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  assert(dst != NULL && src != NULL);
  unsigned char tmp[n];
  memcpy(tmp,src,n);
  memcpy(dst,tmp,n);
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  assert(out != NULL && in != NULL);
  char *dp = out;
  const char *sp = in;
  while (n--)
      *dp++ = *sp++;
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  assert(s1 != NULL && s2 != NULL && n > 0);
  char* p = (char*)s1;
  char* q = (char*)s2;
  while(--n > 0 && *p == *q) {
    p++;
    q++;
  }
  return *p - *q;
}

#endif
