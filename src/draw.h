#ifndef __DRAW_H__
#define __DRAW_H__

#define WIDTH 320
#define HEIGHT 200
#define SCREEN_RAM ((char*)0x6000)
#define BITMAP_ADDR 0x4000
#define BITMAP_RAM ((char*)0x4000)

void line(char x1, char y1, char x2, char y2);

void triangle(char x1, char y1, char x2, char y2, char x3, char y3);

#endif
