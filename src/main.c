#include <c64.h>
#include <string.h>

#define WIDTH 320
#define HEIGHT 200
#define VIC_BITMAP_MODE 32
#define VIC_MULTICOLOR_MODE 16
#define VIC_MEMSETUP 128
#define SCREEN_RAM ((char*)0x6000)
#define BITMAP_ADDR 0x4000
#define BITMAP_RAM ((char*)0x4000)

/* 0x20 + ((i & 0xF8) * 40) */
const unsigned int ylookup[] = {
BITMAP_ADDR+32,
BITMAP_ADDR+352,
BITMAP_ADDR+672,
BITMAP_ADDR+992,
BITMAP_ADDR+1312,
BITMAP_ADDR+1632,
BITMAP_ADDR+1952,
BITMAP_ADDR+2272,
BITMAP_ADDR+2592,
BITMAP_ADDR+2912,
BITMAP_ADDR+3232,
BITMAP_ADDR+3552,
BITMAP_ADDR+3872,
BITMAP_ADDR+4192,
BITMAP_ADDR+4512,
BITMAP_ADDR+4832,
BITMAP_ADDR+5152,
BITMAP_ADDR+5472,
BITMAP_ADDR+5792,
BITMAP_ADDR+6112,
BITMAP_ADDR+6432,
BITMAP_ADDR+6752,
BITMAP_ADDR+7072,
BITMAP_ADDR+7392,
BITMAP_ADDR+7712,
BITMAP_ADDR+8032,
BITMAP_ADDR+8352,
BITMAP_ADDR+8672,
BITMAP_ADDR+8992,
BITMAP_ADDR+9312,
BITMAP_ADDR+9632,
BITMAP_ADDR+9952,
};
 
void line(char x1, char y1, char x2, char y2)
{
  int error, error2;
  int deltaX = x2 - x1;
  int deltaY = y2 - y1;
  if (!(deltaX && deltaY))
    return;
  deltaX = deltaX > 0 ? deltaX : -deltaX;
  deltaY = deltaY < 0 ? deltaY : -deltaY;
  signed char signX = x1 < x2 ? 1 : -1;
  signed char signY = y1 < y2 ? 1 : -1;
  error = deltaX + deltaY;
  while (x1 != x2 || y1 != y2) {
    ((char*)ylookup[y1 >> 3])[(x1 & ~7) + (y1 & 7)] |= 0b10000000 >> (x1 & 7);
    error2 = error << 1;
    if (error2 > deltaY) {
      error += deltaY;
      x1    += signX;
    }
    if (error2 < deltaX) {
      error += deltaX;
      y1    += signY;
    }
  }
}

int main(void)
{
  /* configure vic */
  VIC.bordercolor = COLOR_BLACK;
  VIC.bgcolor0 = COLOR_BLACK;
  VIC.ctrl1 |= VIC_BITMAP_MODE;
  //VIC.ctrl2 |= VIC_MULTICOLOR_MODE;
  *(char*)0x0001 &= ~1;
  CIA2.pra &= ~1;
  VIC.addr = VIC_MEMSETUP;
  /* set pallite */
  memset(SCREEN_RAM, 0x10, 1000);
  //memset((void*)COLOR_RAM, 0x01, 1000);
  /* clearbitmap */
  memset(BITMAP_RAM, 0, 8000);
  line(0, 0, 255, 199);
  return 0;
}
