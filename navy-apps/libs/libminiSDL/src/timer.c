#include <NDL.h>
#include <sdl-timer.h>
#include <stdio.h>
#include <sys/time.h>

SDL_TimerID SDL_AddTimer(uint32_t interval, SDL_NewTimerCallback callback, void *param) {
  return NULL;
}

int SDL_RemoveTimer(SDL_TimerID id) {
  return 1;
}

uint32_t SDL_GetTicks() {
  struct timeval* tv = malloc(sizeof(struct timeval));
  struct timezone* tz = malloc(sizeof(struct timezone));
  gettimeofday(tv, tz);
  return tv->tv_usec / 1000 + tv->tv_sec * 1000;
}

void SDL_Delay(uint32_t ms) {
}
