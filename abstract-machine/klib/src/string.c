// #include <klib.h>
// #include <klib-macros.h>
// #include <stdint.h>

// #if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// size_t min(size_t a, size_t b) {
//   return a <= b ? a : b;
// }

// size_t strlen(const char *s) {
//   assert(s != NULL);
//   size_t len = 0;
//   while(s[len] != '\0') {
//     len++;
//   }
//   return len;
// }

// char *strcpy(char *dst, const char *src) {
//   assert(dst != NULL);
//   assert(src != NULL);
//   size_t i = 0;
//   for(i = 0; src[i] != '\0'; i++) {
//     dst[i] = src[i];
//   }
//   dst[i] = src[i];
//   return dst;
// }

// char *strncpy(char *dst, const char *src, size_t n) {
//   assert(src != NULL && dst != NULL);
//   size_t i;
//   for (i = 0; i < n && src[i] != '\0'; i++)
//       dst[i] = src[i];
//   for ( ; i < n; i++)
//       dst[i] = '\0';

//   return dst;
// }

// char *strcat(char *dst, const char *src) {
//   assert(src != NULL && dst != NULL);
//   size_t  dst_len = strlen(dst);
//   size_t i;
//   for(i = 0; src[i] != '\0'; i++) {
//     dst[dst_len + i] = src[i];
//   }
//   dst[dst_len + i] = '\0';
//   return dst;
// }

// int strcmp(const char *s1, const char *s2) {
//   assert(s1 != NULL && s2 != NULL);
//   size_t len1 = strlen(s1), len2 = strlen(s2);
//   for(int i = 0; i < min(len1, len2); i++) {
//     if(s1[i] > s2[i]) return 1;
//     else if(s2[i] > s1[i]) return -1;
//   }
//   if(len1 > len2) return 1;
//   else if(len2 > len1) return -1;
//   return 0;
// }

// int strncmp(const char *s1, const char *s2, size_t n) {
//   assert(s1 != NULL);
//   if(!n) 
//     return 0;
//   while(--n && *s1 && *s1 == *s2) {
//     s1++;
//     s2++;
//   }
//   return *s1 - *s2;
// }

// void *memset(void *s, int c, size_t n) {
//   assert(s != NULL);
//   char* p = (char*)s;
//   for(size_t i = 0; i < n; i++) {
//     *p = c;
//     p++;
//   }
//   return s;
// }

// void *memmove(void *dst, const void *src, size_t n) {
//   assert(dst != NULL && src != NULL);
//   unsigned char tmp[n];
//   memcpy(tmp,src,n);
//   memcpy(dst,tmp,n);
//   return dst;
// }

// void *memcpy(void *out, const void *in, size_t n) {
//   assert(out != NULL && in != NULL);
//   char *dp = out;
//   const char *sp = in;
//   while (n--)
//       *dp++ = *sp++;
//   return out;
// }

// int memcmp(const void *s1, const void *s2, size_t n) {
//   assert(s1 != NULL && s2 != NULL && n > 0);
//   char* p = (char*)s1;
//   char* q = (char*)s2;
//   while(--n > 0 && *p == *q) {
//     p++;
//     q++;
//   }
//   return *p - *q;
// }

// #endif


#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>
#include <stddef.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  //panic("Not implemented");
  size_t len = 0;
  while(s[len] != '\0'){
    len++;
  }

  return len;
}

char *strcpy(char *dst, const char *src) {
  int i;
  for (i = 0; src[i] != '\0'; ++i){
    dst[i] = src[i];
  }
  dst[i] = '\0';

  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  int i;
  for (i = 0; i < n && src[i] != '\0'; ++i){
    dst[i] = src[i];
  }
  for (; i < n; ++i){
    dst[i] = '\0';
  }

  return dst;
}

char *strcat(char *dst, const char *src) {
  int i, j;
  for (i = 0; dst[i] != '\0'; ++i){}
  for (j = 0; src[j] != '\0'; ++j, ++i){
    dst[i] = src[j];//追加
  }
  dst[i] = '\0';

  return dst;
}

int strcmp(const char *s1, const char *s2) {
  int i;
  for (i = 0; s1[i] != '\0' && s2[i] != '\0'; ++i){
    if (s1[i] != s2[i])
      return (int)(s1[i]) - (int)(s2[i]);
  }
  //case 同时结束：为0
  //case s1先结束，0-x < 0
  //case s2先结束，x-0 > 0
  return (int)(s1[i]) - (int)(s2[i]);
}

int strncmp(const char *s1, const char *s2, size_t n) {
  int i;
  for (i = 0; i < n && s1[i] != '\0' && s2[i] != '\0'; ++i){
    if (s1[i] != s2[i])
      return (int)(s1[i]) - (int)(s2[i]);
  }
  //case 同时结束：为0
  //case s1先结束，0-x < 0
  //case s2先结束，x-0 > 0
  //case 到达n，返回0
  if (i == n)
    return 0;
  return (int)(s1[i]) - (int)(s2[i]);
}

void *memset(void *s, int c, size_t n) {
  unsigned char* target = (unsigned char*)s;
  for (int i = 0; i < n; ++i){
    target[i] = (unsigned char)c;
  }
  return s;
}

// 如果目标区域和源区域有重叠的话，
// memmove() 能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中，
// 复制后源区域的内容会被更改。
void *memmove(void *dst, const void *src, size_t n) {
  char *char_dst = (char *)dst;
  char *char_src = (char *)src;

  if (dst < src){
    for (int i = 0; i < n; ++i)
      char_dst[i] = char_src[i];
  }else if(dst > src){
    for (int i = n-1; i >= 0; --i)
      char_dst[i] = char_src[i];
  }//else 不需要复制

  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  char *char_out = (char *)out;
  const char *char_in = (const char *)in;
  for (int i = 0; i < n; ++i){
    char_out[i] = char_in[i];
  }

  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  char *char_s1 = (char *)s1;
  char *char_s2 = (char *)s2;

  int i;
  for (i = 0; i < n; ++i){
    if (char_s1[i] != char_s2[i])
      return (int)(char_s1[i]) - (int)(char_s2[i]);
  }
  if (i == n)
    return 0;
  return (int)(char_s1[i]) - (int)(char_s2[i]);
}

#endif