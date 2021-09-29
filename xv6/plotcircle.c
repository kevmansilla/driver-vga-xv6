#include "types.h"
#include "stat.h"
#include "user.h"

static void usage(){
  printf(1,"Usage: plotcircle [x0] [y0] [radius] [color]\n");
}

int
main(int argc, char *argv[])
{
  if(argc != 5) {
    usage();
  }else {
    plotcircle(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
  }
  exit();
}
