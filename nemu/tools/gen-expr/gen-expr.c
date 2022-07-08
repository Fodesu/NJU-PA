#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";
int buf_index = 0;
static int choose(int n) {
  return rand() % n;
}
static void gen_rand_op() {
  char op;
  switch(choose(4)) {
    case 0:
      op = '+';
      break;
    case 1:
      op = '-';
      break;
    case 2:
      op = '*';
      break;
    case 3:
      op = '/';
      break;
  }
  buf[buf_index++] = op;
}
static void gen_num() {
  int num = choose(256), size = 0;
  size = snprintf(buf+buf_index, 65536 - buf_index, "%d", num);
  buf_index += size;
}
static void gen(char c) {
  buf[buf_index++] = c;
}
static void gen_rand_expr() {
  switch(choose(3)) {
    case 0 : 
      gen_num();
      break;
    case 1 :
      gen('(');
      gen_rand_expr();
      gen(')');
      break;
    case 2 :
      gen_rand_expr();
      gen_rand_op();
      gen_rand_expr();
      break;
  }
}




int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(code_buf, 0, sizeof(code_buf));
    memset(buf, 0, sizeof(buf));
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
