#include "types.h"
#include "defs.h"
#include "x86.h"
#include "vga.h"
#include "memlayout.h"

void
vgainit()
{
  *(int *)P2V(0xB8F94) = 0x0353;
  *(int *)P2V(0xB8F96) = 0x034F;
  *(int *)P2V(0xB8F98) = 0x0332;
  *(int *)P2V(0xB8F9A) = 0x0330;
  *(int *)P2V(0xB8F9C) = 0x0332;
  *(int *)P2V(0xB8F9E) = 0x0331;
}

static void
clear_screen(int x, int y)
{
  uchar *VGA_G = (uchar *)P2V(0xA0000);
  for (uint i = 0; i < x * y; i++)
    VGA_G[i] = (char)0x00;
}

static void
vgaSetPalette(int index, int r, int g, int b)
{
  outb(0x3C8, index);
  outb(0x3C9, r);
  outb(0x3C9, g);
  outb(0x3C9, b);
}

static void
setdefaultVGApalette()
{
  for(int index = 0; index < 256; index++)
  {
    int value = vga_pal[index];
    vgaSetPalette(index, (value >> 18) & 0x3f, (value >> 10) & 0x3f, (value >> 2) & 0x3f);
  }
}

int
plotpixel(int x, int y, int color)
{
  uchar *VGA = (uchar *)P2V(0xA0000);
  unsigned int offset = 320*y+x;
  VGA[offset] = color;
  return 0;
}

int
plotrectangle(int x1, int y1, int x2, int y2, int color)
{
  for (int i = x1; i < x1 + x2; i++)
  {
    for (int j = y1; j < y1 + y2; j++)
    {
      plotpixel(i, j, color);
    }
  }
  return 0;
}

int
plotcircle(int x0, int y0, int radius, int color)
{
  int x = radius;
  int y = 0;
  int xChange = 1 - (radius << 1);
  int yChange = 0;
  int radiusError = 0;

  while (x >= y){
    for (int i = x0 - x; i <= x0 + x; i++)
    {
      plotpixel(i, y0 + y, color);
      plotpixel(i, y0 - y, color);
    }
    for (int i = x0 - y; i <= x0 + y; i++)
    {
      plotpixel(i, y0 + x, color);
      plotpixel(i, y0 - x, color);
    }

    y++;
    radiusError += yChange;
    yChange += 2;
    if (((radiusError << 1) + xChange) > 0)
    {
      x--;
      radiusError += xChange;
      xChange += 2;
    }
  }

  return 0;
}

static void
write_regs(unsigned char *regs)
{
  uint i = 0u;

/* write MISCELLANEOUS reg */
  outb(VGA_MISC_WRITE, *regs);
  regs++;
/* write SEQUENCER regs */
  for(i = 0u; i < VGA_NUM_SEQ_REGS; i++)
  {
    outb(VGA_SEQ_INDEX, i);
    outb(VGA_SEQ_DATA, *regs);
    regs++;
  }
/* unlock CRTC registers */
  outb(VGA_CRTC_INDEX, 0x03);
  outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) | 0x80);
  outb(VGA_CRTC_INDEX, 0x11);
  outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
  regs[0x03] |= 0x80;
  regs[0x11] &= ~0x80;
/* write CRTC regs */
  for(i = 0u; i < VGA_NUM_CRTC_REGS; i++)
  {
    outb(VGA_CRTC_INDEX, i);
    outb(VGA_CRTC_DATA, *regs);
    regs++;
  }
/* write GRAPHICS CONTROLLER regs */
  for(i = 0u; i < VGA_NUM_GC_REGS; i++)
  {
    outb(VGA_GC_INDEX, i);
    outb(VGA_GC_DATA, *regs);
    regs++;
  }
/* write ATTRIBUTE CONTROLLER regs */
  for(i = 0u; i < VGA_NUM_AC_REGS; i++)
  {
    (void)inb(VGA_INSTAT_READ);
    outb(VGA_AC_INDEX, i);
    outb(VGA_AC_WRITE, *regs);
    regs++;
  }
/* lock 16-color palette and unblank display */
  (void)inb(VGA_INSTAT_READ);
  outb(VGA_AC_INDEX, 0x20);
}

static void
set_font(uchar font[FONT_SIZE])
{
  uint i = 0u;
  uint j = 0u;
  uchar *p = (uchar *) P2V(0xB8000);
  uchar mem_mode, graphics_mode;

  /* Panel 2 write enable */
  outb(VGA_SEQ_INDEX, VGA_SEQ_MAP_MASK_REG);
  outb(VGA_SEQ_INDEX + 1, 0x04);
  /* To be shure, that the first font in the plane 2 is selected */
  outb(VGA_SEQ_INDEX, VGA_SEQ_CHARSET_REG);
  outb(VGA_SEQ_INDEX + 1, 0x00);
  outb(VGA_SEQ_INDEX, VGA_SEQ_MEMORY_MODE_REG);
  mem_mode = inb(VGA_SEQ_INDEX + 1);
  outb(VGA_SEQ_INDEX, VGA_SEQ_MEMORY_MODE_REG);
  outb(VGA_SEQ_INDEX + 1, 0x06);
  outb(VGA_GC_INDEX, VGA_GC_GRAPHICS_MODE_REG);
  graphics_mode = inb(VGA_GC_INDEX + 1);
  outb(VGA_GC_INDEX, VGA_GC_GRAPHICS_MODE_REG);
  outb(VGA_GC_INDEX + 1, 0x00);

   /* Write charmap */
  for(i = 0u; i < CHARSET_LENGTH; i++)
  {
    for(j = 0u; j < BYTES_PER_GLYPTH; j++)
    {
      *p = *font;
      ++p;
      ++font;
    }
    p += BYTES_SKIP;
  }

  /* Restore VGA to normal operation */
  /* Panels 0 and 1 write enable */
  outb(VGA_SEQ_INDEX, VGA_SEQ_MAP_MASK_REG);
  outb(VGA_SEQ_INDEX + 1, 0x03);
  outb(VGA_SEQ_INDEX, VGA_SEQ_MEMORY_MODE_REG);
  outb(VGA_SEQ_INDEX + 1, mem_mode);
  outb(VGA_GC_INDEX, VGA_GC_READ_MAP_SELECT_REG);
  outb(VGA_GC_INDEX + 1, 0x00);
  outb(VGA_GC_INDEX, VGA_GC_GRAPHICS_MODE_REG);
  outb(VGA_GC_INDEX + 1, graphics_mode);
  outb(VGA_GC_INDEX, VGA_GC_MISC_REG);
  outb(VGA_GC_INDEX + 1, 0x0C);
}

int
selec_mode(int mode)
{
  if (mode == INIT_VGA)
  {
    write_regs(g_320x200x256);
    setdefaultVGApalette();
    clear_screen(320,200);
  }
  else if (mode == INIT_TEX_MODE)
  {
    write_regs(g_80x25_text);
    set_font(g_8x16_font);
    clear_screen(80,25);
    vgainit();
  }
  return 0;
}
