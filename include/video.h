#ifndef VIDEO_H_
#define VIDEO_H_

#include <types.h>

void video_set_resolution(u32 xres, u32 yres, u32 bpp);
void video_draw_char(char c, u32 pox_x, u32 pos_y);
void video_draw_string(char *s, u32 pos_x, u32 pos_y);
void video_draw_pixel(u32 x, u32 y, u32 color);
void video_draw_rect(u32 x, u32 y, u32 color);

#endif // VIDEO_H_

