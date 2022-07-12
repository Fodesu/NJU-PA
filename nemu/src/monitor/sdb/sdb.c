#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/vaddr.h>

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();
void new_wp(char* args);
void show_watchpoint();
void free_wp(uint32_t nb);
/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state = NEMU_END;
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args);

static int cmd_info(char *args);

static int cmd_x(char *args);

static int cmd_w(char *args);

static int cmd_d(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "step num seconds", cmd_si},
  { "info", "information for Register or watchpoint", cmd_info},
  {"x", "read memory by virtual address", cmd_x},
  {"p", "print val of expr", cmd_p},
  {"w", "watching the expr change", cmd_w},
  {"d", "delete watchpoint", cmd_d},
  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_d(char *args) {
  int ans = atoi(args);
  if(ans == 0) printf("Error Arguments\n");
  else {
    free_wp(ans);
  }
  return ans;
}

static int cmd_w(char *args) {
  if(args == NULL) {
    printf("No Arguments\n");
    return 0;
  }
  bool* s = (bool*)malloc(sizeof(bool));
  *s = true;
  expr(args, s);
  if(*s == true){
    new_wp(args);
  } else printf("Arguments is not legal\n");
  return 0;
}

int cmd_p(char *args) {
  if(args == NULL) {
    printf("No Arguments\n");
    return 0;
  }
  printf("%s\n", args);
  bool *success = malloc(sizeof(int));
  *success = true; 
  int ans = expr(args, success);
  if(*success == false) Log("get val of expr is Error\n");
  else printf("Ans is %d\n", ans);
  free(success);
  return 0;
}

static int cmd_x(char *args) {
  char *num = NULL;
  char *address = NULL;
  num = strtok(NULL, " ");
  if(num == NULL || atoi(num) <= 0) {
    printf("Error Input 1\n");
    return 0;
  } 
  address = strtok(NULL, " ");
  if(address == NULL || strncmp(address, "0x", 2) != 0 ||
   strtok(NULL, " ") != NULL || strlen(address) < 3) {
    if(address == NULL) printf("Error Input 2\n");
    if(strlen(address) < 4) printf("Error Input 5\n");
    if(strncmp(address, "0x", 2) != 0) printf("Error Input 3\n");
    else printf("Error Input 4\n");
    return 0;
  }
  paddr_t addr = 0;
  for(int i = 2; i < strlen(address); i++) {
    if(address[i] <= '9' && address[i] >= '0') {
      addr = addr * 16 + address[i] - '0';
    }
    else switch(address[i]){
      case 'A' : case 'a':
        addr = addr * 16 + 10;
        break;
      case 'B' : case 'b' :
        addr = addr * 16 + 11;
        break;
      case 'C' : case 'c' :
        addr = addr * 16 + 12;
        break;
      case 'D' : case 'd' :
        addr = addr * 16 + 13;
        break;
      case 'E' : case 'e' :
        addr = addr * 16 + 14;
        break;
      case 'F' : case 'f' :
        addr = addr * 16 + 15;
        break;
    }
  }
  int nums = atoi(num);
  for(int i = 0; i < nums; i++) {
    printf("0x%x   0x%x\n", addr + 4 * i, vaddr_read(addr + 4 * i, 4));
  }
  return 0;
}

static int cmd_info(char *args) {
  char *arg = strtok(NULL, " ");
  if(arg == NULL || strtok(NULL, " ") != NULL) {
    printf("Error input\n");
  } else if(strcmp(arg, "r") == 0) {
    isa_reg_display();
  } else if(strcmp(arg, "w") == 0) {
    show_watchpoint();
  } else printf("Unknow Arguments\n");
  return 0;
}

static int cmd_si(char *args) {
/*                       */ 
 //  Log("success into cmd_si");
  char *arg = strtok(NULL, " ");
  int step = 0;
  if(strtok(NULL, " ") != NULL) {
    printf("Error input\n");
    return 0;
  }
  if(arg == NULL) {
    step = 1;
  //  printf("arg is NULL\n");
  } else if(atoi(arg) > 0) {
  //  printf("arg is digit\n");
    step = atoi(arg);
  } else {
    printf("Error arguments\n");
    return 0;
  }
  cpu_exec(step);
  return 0;
}

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
