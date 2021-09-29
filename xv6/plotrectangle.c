#include "types.h"
#include "stat.h"
#include "user.h"

static void usage(){
  printf(1,"Usage: plotrectangle [x1] [y1] [x2] [y2] [color]\n");
}

int
main(int argc, char *argv[])
{
  if(argc != 6) {
    usage();
  }else {
    plotrectangle(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]));
  }
  exit();
}
