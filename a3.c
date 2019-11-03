#include <stdio.h>
#include <stdlib.h>

#include "name.h"
#include "common.h"
#include "title.h"
#include "principals.h"


int main(int argc, char * argv[]) {
  /*struct name_basics *names;*/
  if (argc != 2) {
    fprintf( stderr, "Usage:  %s directory\n", argv[0] );
    exit(-1);
  }
  getName( argv[1] );
  return 0;
}
