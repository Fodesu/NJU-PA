#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_DIGITAL,
  TK_LPARE, TK_RPARE,TK_COMMA, TK_PLUS, 
  TK_SUB, TK_DIVI, TK_MULTI,

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", TK_PLUS},         // plus
  {"==", TK_EQ},        // equal
  {"(\\?<=[0-9\\)])-", TK_SUB},
  {"^(-[0-9]|[0-9])[0-9]*", TK_DIGITAL},
  {"\\*", TK_MULTI},
  {"\\/", TK_DIVI},
  {"\\(", TK_LPARE},
  {"\\)", TK_RPARE},
  {",", TK_COMMA},
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_PLUS :
                  printf("%d\n", nr_token);
                  tokens[nr_token].type = TK_PLUS;
                  nr_token++;
                  break;
          case TK_SUB :
                  printf("%d\n", nr_token);
                  tokens[nr_token].type = TK_SUB;
                  nr_token++;
                  break;
          case TK_MULTI :
                  printf("%d\n", nr_token);
                  tokens[nr_token].type = TK_MULTI;
                  nr_token++;
                  break;
          case TK_DIVI :
                  printf("%d\n", nr_token);
                  tokens[nr_token].type = TK_DIVI;
                  nr_token++;
                  break;
          case TK_LPARE :
                  printf("%d\n", nr_token);
                  tokens[nr_token].type = TK_LPARE;
                  nr_token++;
                  break;
          case TK_RPARE :
                  printf("%d\n", nr_token);
                  tokens[nr_token].type = TK_RPARE;
                  nr_token++;
                  break;
          case TK_DIGITAL :
                  printf("%d\n", nr_token);
                  tokens[nr_token].type = TK_DIGITAL;
                  if(substr_len < 32){
                         strncpy(tokens[nr_token].str, substr_start, substr_len);  
                         printf("%s\n", tokens[nr_token].str);
                  } else {
                          printf("number too long\n");
                  }
                  nr_token++;
                  break;
        }
        // Log("%c  %s\n", tokens[nr_token-1].type, tokens[nr_token-1].str);
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

static bool check_parentheses(int p, int q) {
  int cnt = 0;
  if(tokens[p].type != TK_LPARE || tokens[q].type != TK_RPARE) {
    return false;
  }
  for(int i = p + 1; i < q; i++) {
    if(tokens[i].type == TK_LPARE) 
      cnt ++;
    else if(tokens[i].type == TK_RPARE){
      if(--cnt < 0)  return false;
    }
      
  }
  if(cnt != 0) return false;
  return true;
}


uint32_t Find_Oper(int p, int q) {
  printf("finding op in the bound %d ~~ %d\n", p, q);
  int cnt = 0, pi = -1, MINN = 3;
  for(int i = q; i >= p; i--) {
    printf("%c\n", tokens[i].type);
    if(tokens[i].type == TK_RPARE) 
      cnt++;
    else if(tokens[i].type == TK_LPARE) 
      cnt--;
    if(cnt < 0) return -1;
    if(cnt == 0 && MINN > 1 && (tokens[i].type == TK_PLUS || tokens[i].type == TK_SUB)){
      MINN = 1;
      pi = i;
    }
    if(cnt == 0 && MINN == 3 && (tokens[i].type == TK_MULTI || tokens[i].type == TK_DIVI)){
      MINN = 2;
      pi = i;
    }
  }
  if(pi != -1) return pi;
  Assert(0, "cannot find main operation");
}
 

uint32_t eval(int p, int q, bool* success) {
  printf("in the %d ~ %d\n", p, q);
  if (p > q) {
    *success = false; 
    printf("Bad Range\n");
    return 0;
  }
  else if (p == q) {
    // printf("%s\n", tokens[p].str);
    return atoi(tokens[p].str);
  }
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1, success);
  }
  else {
    int op = Find_Oper(p, q);
    if(op == -1) success = false;
    printf("%d   %d\n", op, tokens[op].type);
    uint32_t val1 = eval(p, op - 1, success);
    uint32_t val2 = eval(op + 1, q, success);
    printf("%d   %d\n", val1, val2);
    printf("%d   %d\n", op, tokens[op].type);
    if(*success == 1) printf("true\n");
    else printf("Error\n");
    switch (tokens[op].type) {
      case TK_PLUS: return val1 + val2;
      case TK_SUB: return val1 - val2;
      case TK_MULTI: return val1 * val2;
      case TK_DIVI: return val1 / val2;
      default: Assert(0, "Error Main Operation");
    }
  }
}

word_t expr(char *e, bool *success) {
  for(int i = 0; i < 32; i++) {
    tokens[i].type = 0;
    memset(tokens[i].str, 0, sizeof(tokens[i].str));
  }
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  int p = 31;
  while(tokens[p].type == 0) p--;
/* TODO: Insert codes to evaluate the expression. */
  for(int i = 0; i <= p; i++) {
    printf("%s, ", tokens[i].str);
  }
  printf("\n");
  return eval(0, p, success);  
  return 0;
}
