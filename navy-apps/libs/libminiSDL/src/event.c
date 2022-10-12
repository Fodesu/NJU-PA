#include <NDL.h>
#include <SDL.h>
#include <string.h>
#define keyname(k) #k,
#define NUM_KEYNAME (sizeof(keyname) / sizeof(keyname[0]))

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

int SDL_PushEvent(SDL_Event *ev) {
    return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
    char buf[16];
    memset(buf, 0, sizeof(buf));
    if(NDL_PollEvent(buf, 16) == 0) return 0;
    if(strncmp(buf, "ku", 2) == 0) ev->type = SDL_KEYUP;
    else if(strncmp(buf, "kd", 2) == 0) ev->type = SDL_KEYDOWN;
    for(size_t i = 0; i < NUM_KEYNAME; i++) {
        if((strlen(buf + 3) - 1 == strlen(keyname[i])) && strncmp(buf + 3, keyname[i], strlen(keyname[i])) == 0) {
        ev->key.keysym.sym = i;
        break;
        }
    }

    return 1;
}

int SDL_WaitEvent(SDL_Event *event) {
    char buf[16];
    memset(buf, 0, sizeof(buf));
    while(NDL_PollEvent(buf, 16) == 0) {}
    printf("buf = %s\n", buf);
    if(strncmp(buf, "ku", 2) == 0) event->type = SDL_KEYUP;
    else if(strncmp(buf, "kd", 2) == 0) event->type = SDL_KEYDOWN;
    printf("event -> type = %u\n", event->type);
    for(size_t i = 0; i < NUM_KEYNAME; i++) {
        if((strlen(buf + 3) -1  == strlen(keyname[i])) && strncmp(buf + 3, keyname[i], strlen(keyname[i])) == 0) {
        printf("buf = %s, keyname[i] = %s\n", buf, keyname[i]);
        event->key.keysym.sym = i;
        break;
        }
    }
    return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
