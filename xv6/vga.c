#include "types.h"
#include "defs.h"
#include "x86.h"
#include "vga.h"
#include "memlayout.h"

static void write_regs(unsigned char *regs)
{
  unsigned i;

/* write MISCELLANEOUS reg */
  outportb(VGA_MISC_WRITE, *regs);
  regs++;
/* write SEQUENCER regs */
  for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
  {
    outportb(VGA_SEQ_INDEX, i);
    outportb(VGA_SEQ_DATA, *regs);
    regs++;
  }
/* unlock CRTC registers */
  outportb(VGA_CRTC_INDEX, 0x03);
  outportb(VGA_CRTC_DATA, inportb(VGA_CRTC_DATA) | 0x80);
  outportb(VGA_CRTC_INDEX, 0x11);
  outportb(VGA_CRTC_DATA, inportb(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
  regs[0x03] |= 0x80;
  regs[0x11] &= ~0x80;
/* write CRTC regs */
  for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
  {
    outportb(VGA_CRTC_INDEX, i);
    outportb(VGA_CRTC_DATA, *regs);
    regs++;
  }
/* write GRAPHICS CONTROLLER regs */
  for(i = 0; i < VGA_NUM_GC_REGS; i++)
  {
    outportb(VGA_GC_INDEX, i);
    outportb(VGA_GC_DATA, *regs);
    regs++;
  }
/* write ATTRIBUTE CONTROLLER regs */
  for(i = 0; i < VGA_NUM_AC_REGS; i++)
  {
    (void)inportb(VGA_INSTAT_READ);
    outportb(VGA_AC_INDEX, i);
    outportb(VGA_AC_WRITE, *regs);
    regs++;
  }
/* lock 16-color palette and unblank display */
  (void)inportb(VGA_INSTAT_READ);
  outportb(VGA_AC_INDEX, 0x20);
}

int
selec_mode(int mode)
{
  if(mode == 1){
    write_regs(g_320x200x256);
    uchar *VGA = (uchar *) P2V(0xA0000);
    for (uint i = 0; i < 320*200; i++){
      VGA[i] = 0x11;
    }
    return 1;
  }else if (mode == 0){
    write_regs(g_80x25_text);
    return 0;
  }
  return 0;
}

int
plotpixel(int x, int y, int color)
{
  uchar *VGA = (uchar *)P2V(0xA0000);
  unsigned int offset = 320*y + x;
  VGA[offset] = color;
  return 0;
}

int
plotrectangle(int x1, int y1, int x2, int y2, int color)
{
  for(int i = x1; i < x1 + x2; i++){
    for(int j=y1; j < y1 + y2; j++){
      plotpixel(i,j,color);
    }
  }
  return 0;
}
