#include "types.h"
#include "stat.h"
#include "user.h"

static void usage(){
  printf(2,"Usage: modeswitch [option]\n");
  printf(2,"0 -> switch to text mode\n");
  printf(2,"1 -> switch to graphic mode\n");
}

int
main(int argc, char **argv)
{
  if(argc < 2) {
    usage();
  } else if (strcmp(argv[1], "1") == 0 ) {
    printf(2,"Init Graphic Mode\n");
    modeswitch(1);
  } else if (strcmp(argv[1], "0") == 0) {
    printf(2,"Init Text Mode\n");
    modeswitch(0);
  } else {
    usage();
  }

  exit();
}
