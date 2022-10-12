#define SDL_malloc  malloc
#define SDL_free    free
#define SDL_realloc realloc

#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"
#include <sys/stat.h>
#include <stdio.h>
#include <SDL.h>
SDL_Surface* IMG_Load_RW(SDL_RWops *src, int freesrc) {
  assert(src->type == RW_TYPE_MEM);
  assert(freesrc == 0);
  return NULL;
}

SDL_Surface* IMG_Load(const char *filename) {
  struct stat statbuf;
  stat(filename, &statbuf);
  int size = statbuf.st_size;
  FILE* fp = fopen(filename, "r");
  assert(fp);
  char* buf = malloc(size);
  int k = fread(buf, sizeof(buf), size, fp);
  SDL_Surface* ret = STBIMG_LoadFromMemory(buf, size);
  free(fp);
  return ret;
}

int IMG_isPNG(SDL_RWops *src) {
  return 0;
}

SDL_Surface* IMG_LoadJPG_RW(SDL_RWops *src) {
  return IMG_Load_RW(src, 0);
}

char *IMG_GetError() {
  return "Navy does not support IMG_GetError()";
}
