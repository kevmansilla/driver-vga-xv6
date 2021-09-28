#include "types.h"
#include "stat.h"
#include "user.h"

void
plotsquare(int x, int y, int size, int color)
{
  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j < size; j++)
    {
      plotpixel(x + j, y + i, color);
    }
  }
}

// Return a integer between 0 and ((2^32 - 1) / 2), which is 2147483647.
static uint
random(void)
{
  static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
  unsigned int b;
  b = ((z1 << 6) ^ z1) >> 13;
  z1 = ((z1 & 4294967294U) << 18) ^ b;
  b = ((z2 << 2) ^ z2) >> 27;
  z2 = ((z2 & 4294967288U) << 2) ^ b;
  b = ((z3 << 13) ^ z3) >> 21;
  z3 = ((z3 & 4294967280U) << 7) ^ b;
  b = ((z4 << 3) ^ z4) >> 12;
  z4 = ((z4 & 4294967168U) << 13) ^ b;
  return (z1 ^ z2 ^ z3 ^ z4) / 2;
}

// Return a random integer between a given range.
static int
randomrange(int lo, int hi)
{
  if (hi < lo)
  {
    int tmp = lo;
    lo = hi;
    hi = tmp;
  }
  int range = hi - lo + 1;
  return random() % (range) + lo;
}

static int
plotsky()
{
  plotrectangle(0, 0, 320, 200, 0xC6);
  return 0;
}

static int
grass_block(int x, int y)
{
  plotrectangle(x, y, 40, 7, 0x77);
  plotrectangle(x, y + 7, 40, 33, 0xBA);
  for (uint i = 0; i < 40; i++)
  {
    uint ran = randomrange(0, 39);
    plotpixel(x + ran, y + 7, 0x77);
    plotpixel(x + ran, y + 8, 0x77);
  }
  for (uint i = 0; i < 10; i++)
  {
    for (uint j = 0; j < 30; j++)
    {
      uint ran2 = randomrange(0, 39);
      plotpixel(x + ran2, y + 9 + j, 0x72);
    }
  }
  return 0;
}

static int
plotstar()
{
  for (uint i = 0; i < 600; i++)
  {
    uint ran_x = randomrange(0, 319);
    uint ran_y = randomrange(0, 159);
    plotpixel(ran_x, ran_y, 0x0F);
  }
  return 0;
}

static int
plotgrass()
{
  uint j_temp = 0;
  for (uint i = 0; i < 8; i++)
  {
    grass_block(j_temp, 160);
    j_temp += 40;
  }
  return 0;
}

static int
plotmoon()
{
  plotcircle(55, 50, 1, 0x0f);
  plotcircle(70, 15, 15, 0x1e);
  plotcircle(45, 7, 10, 0x1e);
  return 0;
}

static int 
rocket[] = {
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x40,0x40,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x40,0x40,0x40,0x40,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1C,0x1C,0x1C,0x1C,0x40,0x40,0x1C,0x1C,0x1C,0x1B,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1C,0x1C,0x1C,0x40,0x4D,0x4D,0x40,0x1C,0x1B,0x1B,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1C,0x1C,0x40,0x4D,0x4D,0x4D,0x4D,0x40,0x1B,0x1B,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1C,0x40,0x4D,0x4D,0x4D,0x4D,0x64,0x64,0x40,0x1B,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1C,0x40,0x4D,0x4D,0x4D,0x64,0x64,0x4D,0x40,0x1B,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0x0C,0x1A,0x1C,0x40,0x4D,0x4D,0x64,0x64,0x4D,0x4D,0x40,0x1B,0x1A,0x0C,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0x0C,0x40,0x1A,0x1C,0x1C,0x40,0x64,0x64,0x4D,0x4D,0x40,0x1B,0x1B,0x1A,0x40,0x0C,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x1A,0x1C,0x1C,0x1B,0x40,0x4D,0x4D,0x40,0x1B,0x1B,0x1B,0x1A,0x40,0x40,0x0C,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0x0C,0x40,0x40,0x1A,0x1C,0x1B,0x1B,0x1B,0x40,0x40,0x1B,0x1B,0x1B,0x1B,0x1A,0x40,0x40,0x0C,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0x0C,0x40,0x0C,0x1A,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1A,0x0C,0x40,0x0C,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0x0C,0x0C,0xC6,0x1A,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1A,0xC6,0x0C,0x0C,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0x0C,0xC6,0xC6,0x1A,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1A,0xC6,0xC6,0x0C,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1A,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1A,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1A,0x1A,0x1A,0x1A,0x1A,0x1A,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
};

static int 
smoke[] = {
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1E,0x1E,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1E,0x1E,0x1E,0x1E,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1E,0x1E,0x1F,0x1F,0x1E,0x1E,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1E,0x1E,0x1E,0x1F,0x1F,0x1F,0x1F,0x1E,0x1E,0x1E,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0x1E,0x1E,0x1E,0x1E,0x1E,0x1F,0x1F,0x0F,0x0F,0x1F,0x1F,0x1F,0x1E,0x1E,0x1E,0x1E,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0x1E,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x1F,0x1E,0x1E,0xC6,0xC6,0xC6,
  0xC6,0x1E,0x1E,0x1E,0x1F,0x1F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x1F,0x1F,0x1E,0x1E,0x1E,0xC6,
  0x1E,0x1E,0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x1E,0x1E
};

static int 
linesmoke[] = {
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1E,0x1F,0x1F,0x1E,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,
  0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x1E,0x1F,0x1F,0x1E,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6
};

static int
plotrocket(int x, int y, int scale)
{
  for (int j = 0; j < 23; j++)
  {
    for (int i = 0; i < 24; i++)
    {
      plotsquare(x + (scale * i), y + (scale * j), scale, rocket[24 * j + i]);
    }
  }
  return 0;
}

static int
plotsmoke(int x, int y, int scale)
{
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 24; i++)
    {
      plotsquare(x + (scale * i), y + (scale * j), scale, smoke[24 * j + i]);
    }
  }
  return 0;
}

static int
plotlinesmoke(int x, int y, int scale)
{
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 24; i++)
    {
      plotsquare(x + (scale * i), y + (scale * j), scale, linesmoke[24 * j + i]);
    }
  }
  return 0;
}

int letra_s[] = {
  0,0,67,67,67,67,67,67,0,0,
  0,67,67,67,67,67,67,67,67,0,
  68,68,68,0,0,0,68,68,68,0,
  68,68,68,0,0,0,0,0,0,0,
  0,69,69,69,69,69,0,0,0,0,
  0,0,67,67,67,67,67,0,0,0,
  0,0,0,67,67,67,67,67,0,0,
  0,0,0,0,68,68,68,68,68,0,
  0,0,0,0,0,68,68,68,68,68,
  69,69,69,0,0,0,69,69,69,69,
  69,69,69,69,69,69,69,69,69,69,
  0,67,67,67,67,67,67,67,67,0,
  0,0,67,67,67,67,67,67,0,0
};

int letra_o[] = {
  0,0,67,67,67,67,67,67,0,0,
  0,67,67,67,67,67,67,67,67,0,
  68,68,68,68,68,68,68,68,68,68,
  68,68,68,0,0,0,0,68,68,68,
  69,69,69,0,0,0,0,69,69,69,
  69,69,69,0,0,0,0,69,69,69,
  67,67,67,0,0,0,0,67,67,67,
  67,67,67,0,0,0,0,67,67,67,
  68,68,68,0,0,0,0,68,68,68,
  68,68,68,0,0,0,0,68,68,68,
  67,67,67,67,67,67,67,67,67,0,
  0,67,67,67,67,67,67,67,67,0,
  0,0,68,68,68,68,86,68,0,0
};

int num_2[] = {
  0,0,67,67,67,67,67,67,0,0,
  0,67,67,67,67,67,67,67,67,0,
  68,68,68,68,68,68,68,68,68,68,
  68,68,68,0,0,0,68,68,68,68,
  69,69,69,0,0,69,69,69,0,0,
  69,69,69,0,69,69,69,0,0,0,
  0,0,0,67,67,67,0,0,0,0,
  0,0,67,67,67,0,0,0,0,0,
  0,68,68,68,0,0,0,0,0,0,
  68,68,68,68,0,0,0,0,0,0,
  69,69,69,69,69,69,69,69,69,69,
  69,69,69,69,69,69,69,69,69,69,
  67,67,67,67,67,67,67,67,67,69,
};

int num_0[] = {
  0,0,67,67,67,67,67,67,0,0,
  0,67,67,67,67,67,67,67,67,0,
  68,68,68,68,68,68,68,68,68,68,
  68,68,68,0,0,0,0,68,68,68,
  69,69,69,69,0,0,0,69,69,69,
  69,69,69,69,69,0,0,69,69,69,
  67,67,67,0,67,67,0,67,67,67,
  67,67,67,0,0,67,67,67,67,67,
  68,68,68,0,0,0,68,68,68,68,
  68,68,68,0,0,0,0,68,68,68,
  0,69,69,69,69,69,69,69,69,0,
  0,69,69,69,69,69,69,69,69,0,
  0,0,67,67,67,67,67,67,0,0
};

int num_1[] = {
  0,0,0,67,67,67,0,0,0,0,
  0,67,67,67,67,67,0,0,0,0,
  68,68,68,68,68,68,0,0,0,0,
  68,68,68,68,68,68,0,0,0,0,
  0,0,0,69,69,69,0,0,0,0,
  0,0,0,69,69,69,0,0,0,0,
  0,0,0,67,67,67,0,0,0,0,
  0,0,0,67,67,67,0,0,0,0,
  0,0,0,68,68,68,0,0,0,0,
  0,0,0,68,68,68,0,0,0,0,
  0,69,69,69,69,69,69,69,0,0,
  0,69,69,69,69,69,69,69,0,0,
  0,67,67,67,67,67,67,67,0,0
};

// static void
// clear(int x, int y, int color)
// {
//   plotrectangle(0,0,x,y,color);
// }

static int
putletter(int x, int y, int scale, int letra[])
{
  for (int j = 0; j < 12; j++)
  {
    for (int i = 0; i < 10; i++)
    {
      plotsquare(x + (scale * i), y + (scale * j), scale, letra[10 * j + i]);
    }
  }
  return 0;
}

int main(void)
{
  modeswitch(1);

  // Draw sky:
  plotsky();

  // Draw grass:
  plotgrass();

  // Draw stars:
  plotstar();

  // Draw moon:
  plotmoon();

  // Draw rocket
  plotrocket(200, 67, 3);

  // Draw smoke
  plotsmoke(200, 136, 3);

  // Move rocket: (re-drawing)
  sleep(50);
  for (uint i = 0; i < 30; i++){
    plotrocket(200, 67-5*i, 3);
    plotlinesmoke(200, 136-5*i, 3);
  }

  // Final screen:
  for (uint i = 0; i <= 200; i++)
  {
    plotrectangle(0, 200-i, 320, 1, 00);
    sleep(5);
  }

  //print message
  putletter(20,50,5,letra_s);
  putletter(60,50,5,letra_o);
  putletter(110,50,5,num_2);
  putletter(160,50,5,num_0);
  putletter(210,50,5,num_2);
  putletter(250,50,5,num_1);


  exit();
}
