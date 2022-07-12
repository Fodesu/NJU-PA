#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char* args;
  uint32_t preval;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = (WP*)malloc(sizeof(WP));
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp(char* args) {
 Assert(free_->next != NULL, "free_->next is NULL\n");
 WP* tmp = free_->next;
 free_->next = tmp->next;
 tmp->next = head->next;
 head->next = tmp;
 tmp->args = args;
 Log("In the new_wp function");
 return tmp;
}

void free_wp(WP *wp, uint32_t nb) {
  uint32_t ct = 1;
  WP* cur = head;
  while(ct < nb) {
    cur = cur->next;
  }
  cur->next = cur->next->next;
  wp->next = free_->next;
  free_->next = wp;
}

void check_watchpiont() {
  WP* cur = head;
  while(cur->next != NULL) {
    uint32_t newval = cmd_p(cur->args);
    if(newval != cur->next->preval) {
      printf("No%d: expr- %s 's val is change from %d, %d", cur->NO, cur->args, cur->preval, newval);
      nemu_state.state = NEMU_STOP;
    }
    cur = cur->next;
  }
}
