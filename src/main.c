#include <c64.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 320
#define HEIGHT 200
#define VIC_BITMAP_MODE 32
#define VIC_MULTICOLOR_MODE 16
#define VIC_MEMSETUP 8 | 3 << 4
#define SCREEN_RAM 0xCC00
#define BITMAP_RAM 0xA000
#define REAL_BITMAP_RAM 0xE000

static void plot(unsigned int x, unsigned int y)
{
  ((unsigned char*)BITMAP_RAM)[(y / 8) * WIDTH + (y & 7) + (x / 8) * 8] |= 0b11000000 >> (x & 6);
}

int main(void)
{
  unsigned int x = 0;
  int y = 64;
  int d = 1 - 4 * y;
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
  /* clearbitmap */
  memset((void*)BITMAP_RAM, 0, 8000);
  while (x <= y) {
    plot(x + WIDTH / 2, y + HEIGHT / 2);
    plot(-x + WIDTH / 2, y + HEIGHT / 2);
    plot(x + WIDTH / 2, -y + HEIGHT / 2);
    plot(-x + WIDTH / 2, -y + HEIGHT / 2);
    plot(y + WIDTH / 2, x + HEIGHT / 2);
    plot(-y + WIDTH / 2, x + HEIGHT / 2);
    plot(y + WIDTH / 2, -x + HEIGHT / 2);
    plot(-y + WIDTH / 2, -x + HEIGHT / 2);
    d += 8 * x + 4;
    if (d>=0) {
      y--;
      d -= 8 * y;
    }
    x++;
  }
  memcpy((void*)REAL_BITMAP_RAM, (void*)BITMAP_RAM, 8000);
  return 0;
}
