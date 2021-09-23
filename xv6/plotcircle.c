#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 5) {
    printf(1, "Usage:....\n");
  }else {
    plotcircle(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
  }
  exit();
}
