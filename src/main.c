#include <c64.h>
#include <string.h>
#include "draw.h"

#define VIC_BITMAP_MODE 32
#define VIC_MULTICOLOR_MODE 16
#define VIC_MEMSETUP 128

int main(void)
{
  /* configure vic */
  VIC.bordercolor = COLOR_BLACK;
  VIC.bgcolor0 = COLOR_BLACK;
  VIC.ctrl1 |= VIC_BITMAP_MODE;
#if !LINE_MODE
  VIC.ctrl2 |= VIC_MULTICOLOR_MODE;
#endif
  *(char*)0x0001 &= ~1;
  CIA2.pra &= ~1;
  VIC.addr = VIC_MEMSETUP;
  /* set pallite */
  memset(SCREEN_RAM, 0x10, 1000);
  while (1) {
  /* clearbitmap */
  memset(BITMAP_RAM, 0, 8000);
  triangle(196, 63, 48, 7, 176, 168);
  }
  return 0;
}
