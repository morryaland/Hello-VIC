#include <string.h>
#include "draw.h"

static unsigned int g_cleanbuff[800];
__zp static unsigned int g_clean_c;

#define BA BITMAP_ADDR
/* 0x20 + ((i & 0xF8) * 40) */
const unsigned int ylookup[] = {
BA+32, BA+352, BA+672, BA+992, BA+1312, BA+1632, BA+1952, BA+2272,
BA+2592, BA+2912, BA+3232, BA+3552, BA+3872, BA+4192, BA+4512, BA+4832,
BA+5152, BA+5472, BA+5792, BA+6112, BA+6432, BA+6752, BA+7072, BA+7392,
BA+7712, BA+8032, BA+8352, BA+8672, BA+8992, BA+9312, BA+9632, BA+9952,
};
#undef BA
 
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
    *((char*)((g_cleanbuff[g_clean_c++] = ylookup[y1 >> 3] + (x1 & ~7)) + (y1 & 7))) |= 0b10000000 >> (x1 & 7);
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

void clean(void)
{
  while (g_clean_c--) {
    unsigned int *addr = (unsigned int*)g_cleanbuff[g_clean_c];
    *(addr++) = 0; *(addr++) = 0; *(addr++) = 0; *(addr++) = 0;
    *(addr++) = 0; *(addr++) = 0; *(addr++) = 0; *addr = 0;
  }
}
