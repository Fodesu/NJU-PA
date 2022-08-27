#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

char* reverse(char * str) {
    char *head=str;//指向字符串首
    char *tail=str;//指向字符串尾
    while (*tail){ //*tail!='\0'
        ++tail;
    }
    --tail;
    char temp;
    while (head < tail){
        temp = *head;
        *head++ = *tail;
        *tail-- = temp;
    }
    return str;
}

//my_itoa
char* itoa(int a){
    int n = a;
    if (a < 0){
        a = -a;//如果是负数先转化为正数
    }
    static char str[100];//这里的str必须是静态变量或全局变量
    int i = 0;
    while (a>0) {//从低位开始变为字符，最后进行翻转 
        str[i++] = a % 10 + '0';//将数字转为字符串
        a = a / 10;
    }
    if (n < 0) {//如果是负数加上‘-’号
        str[i++] = '-';
    }
    str[i] = '\0';
    return reverse(str);
}

void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
    



#endif
  return NULL;
}

void free(void *ptr) {
}

#endif
