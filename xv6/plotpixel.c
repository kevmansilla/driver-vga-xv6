#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  if(argc < 4) {
    printf(2,"Usage: modeswitch -> 1 for graphic mode and 0 for text mode\n");
    exit();
  }else {
    plotpixel(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
  }
  exit();
}
