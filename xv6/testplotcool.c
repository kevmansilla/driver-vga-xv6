#include "types.h"
#include "stat.h"
#include "user.h"

// Return a integer between 0 and ((2^32 - 1) / 2), which is 2147483647.
static uint
random(void)
{
  static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
  unsigned int b;
  b  = ((z1 << 6) ^ z1) >> 13;
  z1 = ((z1 & 4294967294U) << 18) ^ b;
  b  = ((z2 << 2) ^ z2) >> 27; 
  z2 = ((z2 & 4294967288U) << 2) ^ b;
  b  = ((z3 << 13) ^ z3) >> 21;
  z3 = ((z3 & 4294967280U) << 7) ^ b;
  b  = ((z4 << 3) ^ z4) >> 12;
  z4 = ((z4 & 4294967168U) << 13) ^ b;

  return (z1 ^ z2 ^ z3 ^ z4) / 2;
}

// Return a random integer between a given range.
static int
randomrange(int lo, int hi)
{
  if (hi < lo) {
    int tmp = lo;
    lo = hi;
    hi = tmp;
  }
  int range = hi - lo + 1;
  return random() % (range) + lo;
}

static int 
plotsky(){

  plotrectangle(0, 0, 320, 200, 0xC6);
  return 0;

}

static int 
grass_block(int x, int y)
{

  plotrectangle(x, y, 40, 7, 0x77); 
  plotrectangle(x, y+7, 40, 33, 0xBA); 
  for (uint i = 0; i < 40; i++){
    uint ran = randomrange(0, 39);
    plotpixel(x+ran, y+7, 0x77);
    plotpixel(x+ran, y+8, 0x77);
  }
  for (uint i = 0; i < 10; i++){
    for (uint j = 0; j < 30; j++){
      uint ran2 = randomrange(0, 39);
      plotpixel(x+ran2, y+9+j, 0x72);
    }
  }
  
  return 0;
}

static int 
plotstar(){
 for (uint i = 0; i < 600; i++){
      uint ran_x = randomrange(0, 319);
      uint ran_y = randomrange(0, 159);
      plotpixel(ran_x, ran_y, 0x0F);
  }
  return 0;
}

static int 
plotgrass(){
  uint j_temp = 0;
  for (uint i = 0; i < 8; i++){
    grass_block(j_temp, 160);
    j_temp += 40;
  }
  return 0;
}

static int 
plotmoon(){
  plotcircle(55, 50, 1, 0x0f);
  plotcircle(70, 15, 15, 0x1e);
  plotcircle(45, 7, 10, 0x1e);
  return 0;
}

int
main(void)
{
  modeswitch(1);

  // Draw sky:
  plotsky();

  // Draw grass:
  plotgrass();

  // Draw stars:
  plotstar();  

  // Draw mon:
  plotmoon();



  exit();
}

