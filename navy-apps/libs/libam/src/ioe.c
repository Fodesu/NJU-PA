// #include <am.h>
// #include <klib-macros.h>


// void __am_timer_init();
// void __am_gpu_init();
// void __am_audio_init();
// void __am_input_keybrd(AM_INPUT_KEYBRD_T *);
// void __am_timer_rtc(AM_TIMER_RTC_T *);
// void __am_timer_uptime(AM_TIMER_UPTIME_T *);
// void __am_gpu_config(AM_GPU_CONFIG_T *);
// void __am_gpu_status(AM_GPU_STATUS_T *);
// void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *);
// void __am_audio_config(AM_AUDIO_CONFIG_T *);
// void __am_audio_ctrl(AM_AUDIO_CTRL_T *);
// void __am_audio_status(AM_AUDIO_STATUS_T *);
// void __am_audio_play(AM_AUDIO_PLAY_T *);
// void __am_disk_config(AM_DISK_CONFIG_T *cfg);
// void __am_disk_status(AM_DISK_STATUS_T *stat);
// void __am_disk_blkio(AM_DISK_BLKIO_T *io);

// static void __am_timer_config(AM_TIMER_CONFIG_T *cfg) { cfg->present = true; cfg->has_rtc = true; }
// static void __am_input_config(AM_INPUT_CONFIG_T *cfg) { cfg->present = true;  }
// static void __am_uart_config(AM_UART_CONFIG_T *cfg)   { cfg->present = false; }
// static void __am_net_config (AM_NET_CONFIG_T *cfg)    { cfg->present = false; }

// typedef void (*handler_t)(void *buf);
// static void *lut[128] = {
//   [AM_TIMER_CONFIG] = __am_timer_config,
//   [AM_TIMER_RTC   ] = __am_timer_rtc,
//   [AM_TIMER_UPTIME] = __am_timer_uptime,
//   [AM_INPUT_CONFIG] = __am_input_config,
//   [AM_INPUT_KEYBRD] = __am_input_keybrd,
//   [AM_GPU_CONFIG  ] = __am_gpu_config,
//   [AM_GPU_FBDRAW  ] = __am_gpu_fbdraw,
//   [AM_GPU_STATUS  ] = __am_gpu_status,
//   [AM_UART_CONFIG ] = __am_uart_config,
//   [AM_AUDIO_CONFIG] = __am_audio_config,
//   [AM_AUDIO_CTRL  ] = __am_audio_ctrl,
//   [AM_AUDIO_STATUS] = __am_audio_status,
//   [AM_AUDIO_PLAY  ] = __am_audio_play,
//   [AM_DISK_CONFIG ] = __am_disk_config,
//   [AM_DISK_STATUS ] = __am_disk_status,
//   [AM_DISK_BLKIO  ] = __am_disk_blkio,
//   [AM_NET_CONFIG  ] = __am_net_config,
// };

// static void fail(void *buf) { panic("access nonexist register"); }

// bool ioe_init() {
//   for (int i = 0; i < LENGTH(lut); i++)
//     if (!lut[i]) lut[i] = fail;
//   __am_gpu_init();
//   __am_timer_init();
//   return true;
// }

// void ioe_read (int reg, void *buf) { 
//   ((handler_t)lut[reg])(buf); 
// }
// void ioe_write(int reg, void *buf) { 
//   ((handler_t)lut[reg])(buf); 
// }



#include "NDL.h"
#include "../../libminiSDL/include/SDL.h"
#include <am.h>
#include <string.h>
#include <unistd.h>
#include <amdev.h>



static int fb = -1, evt = -1, disp = -1;
static int screen_w, screen_h;
static uint64_t uptime;
bool ioe_init()
{
    evt = open("/dev/events", 0, 0);
    disp = open("/proc/dispinfo", 0, 0);
    fb = open("/dev/fb", 0, 0);
    uptime = ((uint64_t)NDL_GetTicks()) * 1000;
    NDL_Init(0);
    return true;
}

void ioe_read(int reg, void *buf)
{
    char buf2[128];
    SDL_Event ev;
    switch (reg) {
    case AM_TIMER_CONFIG:
        ((AM_TIMER_CONFIG_T *)buf)->has_rtc = true;
        ((AM_TIMER_CONFIG_T *)buf)->present = true;
        break;
    case AM_INPUT_CONFIG:
        ((AM_INPUT_CONFIG_T *)buf)->present = true;
        break;
    case AM_TIMER_UPTIME:
        ((AM_TIMER_UPTIME_T *)buf)->us = ((uint64_t)NDL_GetTicks()) * 1000 - uptime;
        break;
    case AM_INPUT_KEYBRD:
        SDL_PollEvent(&ev);
        ((AM_INPUT_KEYBRD_T *)buf)->keycode = ev.key.keysym.sym;
        ((AM_INPUT_KEYBRD_T *)buf)->keydown = !ev.type;
        break;
    case AM_GPU_CONFIG:
        read(disp, &buf2, 128);
        sscanf(buf2, "WIDTH: %d\nHEIGHT: %d\n", &screen_w, &screen_h);
        ((AM_GPU_CONFIG_T *)buf)->width = screen_w;
        ((AM_GPU_CONFIG_T *)buf)->height = screen_h;
        ((AM_GPU_CONFIG_T *)buf)->vmemsz = screen_w * screen_h * 32;
        ((AM_GPU_CONFIG_T *)buf)->has_accel = false;
        ((AM_GPU_CONFIG_T *)buf)->present = true;
        break;
    case AM_GPU_STATUS:
        ((AM_GPU_STATUS_T *)buf)->ready = true;
        break;
    default:
        printf("unimplimented! ioe_read %d\n",reg);
        break;
    }
}
void ioe_write(int reg, void *buf)
{
    // char *pixels;
    // int x, y, w, h;
    switch (reg) {
    case AM_GPU_FBDRAW:
        NDL_DrawRect(((AM_GPU_FBDRAW_T *)buf)->pixels,
                     ((AM_GPU_FBDRAW_T *)buf)->x,
                     ((AM_GPU_FBDRAW_T *)buf)->y,
                     ((AM_GPU_FBDRAW_T *)buf)->w,
                     ((AM_GPU_FBDRAW_T *)buf)->h);
        break;
    default:
        printf("unimplimented! ioe_write %d\n",reg);
        break;
    }
}
