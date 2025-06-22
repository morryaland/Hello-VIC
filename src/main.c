#include <c64.h>
#include <string.h>

#define WIDTH 320
#define HEIGHT 200
#define VIC_BITMAP_MODE 32
#define VIC_MULTICOLOR_MODE 16
#define VIC_MEMSETUP 8 | 3 << 4
#define SCREEN_RAM 0xCC00
#define BITMAP_RAM 0xA000
#define REAL_BITMAP_RAM 0xE000

void plot(unsigned int x, unsigned int y)
{
  ((unsigned char*)BITMAP_RAM)[(y >> 3) * WIDTH + (y & 7) + (x >> 3) * 8] |= 0b11000000 >> (x & 6);
}

void line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
  int error, error2;
  int deltaX = x2 - x1;
  int deltaY = y2 - y1;
  if (!(deltaX && deltaY))
    return;
  deltaX = deltaX > 0 ? deltaX : -deltaX;
  deltaY = deltaY > 0 ? deltaY : -deltaY;
  int signX = x1 < x2 ? 1 : -1;
  int signY = y1 < y2 ? 1 : -1;
  error = deltaX - deltaY;
  plot(x2, y2);
  while (x1 != x2 || y1 != y2) {
    plot(x1, y1);
    error2 = error * 2;
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

int main(void)
{
  unsigned int x1, x2, y1, y2, seed = 3310;
  /* configure vic */
  VIC.bordercolor = COLOR_BLACK;
  VIC.bgcolor0 = COLOR_BLACK;
  VIC.ctrl1 |= VIC_BITMAP_MODE;
  VIC.ctrl2 |= VIC_MULTICOLOR_MODE;
  *(char*)0x0001 &= ~1;
  CIA2.pra &= ~3;
  VIC.addr = VIC_MEMSETUP;
  /* set pallite */
  memset((void*)SCREEN_RAM, 0x00, 1000);
  memset((void*)COLOR_RAM, 0x01, 1000);
  while (1) {
    x1 = (seed = (5 * seed + 1)) % WIDTH;
    x2 = (seed = (5 * seed + 1)) % WIDTH;
    y1 = (seed = (5 * seed + 1)) % HEIGHT;
    y2 = (seed = (5 * seed + 1)) % HEIGHT;
    if (!(seed % 3)) {
      /* swap */
      memcpy((void*)REAL_BITMAP_RAM, (void*)BITMAP_RAM, 8000);
      /* clearbitmap */
      memset((void*)BITMAP_RAM, 0, 8000);
    }
    line(x1, y1, x2, y2);
  }
  return 0;
}
