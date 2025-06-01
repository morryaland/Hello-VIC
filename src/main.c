#include <c64.h>
#include <string.h>

#define WIDTH 320
#define VIC_BANK 0
#define VIC_BITMAP_MODE 32

#if VIC_BANK == 1
#define VIC_MEMSETUP 128
#define SCREEN 0xA000
#define BITMAP 0x8000
#else
#define VIC_MEMSETUP 8 | 3 << 4
#define SCREEN 0xCC00
#define BITMAP 0xE000
#endif

static inline void setpix(unsigned int x, unsigned int y)
{
  ((char*)BITMAP)[y + WIDTH * (y / 8)] = 0b10000000 >> (x % 8);
}

int main(void)
{
  unsigned char i;
  VIC.bordercolor = COLOR_BLACK;
  VIC.bgcolor0 = COLOR_BLACK;
  VIC.ctrl1 |= VIC_BITMAP_MODE;
  CIA2.pra &= ~3;
#if VIC_BANK
  CIA2.pra |= VIC_BANK; 
#endif
  VIC.addr = VIC_MEMSETUP;
  /* set pallite */
  memset((void*)SCREEN, 0x10, 1000);
  /* clear bitmap */
  memset((void*)BITMAP, 0, 8000);
  for (i = 0; i < 200; ++i) {
    setpix(i, i);
  }
  return 0;
}
