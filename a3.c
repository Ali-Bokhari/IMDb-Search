#include <stdio.h>
#include <stdlib.h>

#include "name.h"
#include "common.h"
#include "title.h"
#include "principals.h"
#include "binary.h"


int main(int argc, char * argv[]) {
  struct name_basics_array *names_basic;
  struct name_basics *name;
  if (argc != 2) {
    fprintf( stderr, "Usage:  %s directory\n", argv[0] );
    exit(-1);
  }
  names_basic = get_name( argv[1] );

  build_pnindex( names_basic );

  name = find_primary_name( names_basic, "Anthony Daniels" );

  printf( "%p\n", (void *)name );

  printf( "%s\n", name->nconst );

  printf( "%s\n", name->primaryName );
  return 0;
}
