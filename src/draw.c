#include "draw.h"

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
  signed char signX, signY;
  char deltaX, deltaY;
  if (x1 < x2) {
    deltaX = x2 - x1;
    signX = 1;
  }
  else {
    deltaX = x1 - x2;
    signX = -1;
  }
  if (y1 < y2) {
    deltaY = y2 - y1;
    signY = 1;
  }
  else {
    deltaY = y1 - y2;
    signY = -1;
  }
  error = deltaX - deltaY;
  while (x1 != x2 || y1 != y2) {
    ((char*)ylookup[y1 >> 3])[(x1 & ~7) | (y1 & 7)] |= 0b10000000 >> (x1 & 7);
    error2 = error << 1;
    if (error2 > -deltaY) {
      error -= deltaY;
      x1    += signX;
    }
    if (error2 < deltaX) {
      error += deltaX;
      y1    += signY;
    }
  }
}
void triangle(char x1, char y1, char x2, char y2, char x3, char y3)
{
#if LINE_MODE
  line(x1, y1, x2, y2);
  line(x2, y2, x3, y3);
  line(x3, y3, x1, y1);
#endif
}
