#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  if(argc < 2) {
    printf(2,"Usage: modeswitch -> 1 for graphic mode and 0 for text mode\n");
    exit();
  }else {
    modeswitch(atoi(argv[1]));
  }
  exit();
}
