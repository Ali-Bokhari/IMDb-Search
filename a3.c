#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "name.h"
#include "common.h"
#include "title.h"
#include "principals.h"
#include "binary.h"


int main(int argc, char * argv[]) {
  struct title_basics_array *title_basics;
  struct title_basics *title;
  struct name_basics_array *name_basics;
  struct name_basics *name;
  struct title_principals_array *title_principals;
  struct title_principals *principals;
  char first[20];
  char second[20];
  if (argc != 2) {
    fprintf( stderr, "Usage:  %s directory\n", argv[0] );
    exit(-1);
  }

  title_basics = get_title( argv[1] );

  build_ptindex( title_basics );

  build_tindex( title_basics );

  printf("lines: %d\n", title_basics->num);

  name_basics = get_name( argv[1] );


  build_pnindex( name_basics );

  build_nindex( name_basics );

  printf("lines: %d\n", name_basics->num);

  title_principals = get_principals( argv[1] );


  build_pntindex( title_principals );

  build_pncindex( title_principals );

  printf("lines: %d\n", title_principals->num);

  while (1) {
    printf("> ");
    scanf("%5s %100s", first, second);
    printf("%s: %s\n", first, second);

    if (strcmp(first, "name") == 0) {
      name = find_primary_name( name_basics, second );
      principals = find_principals_nconst( title_principals, name->nconst );
      title = find_primary_title( title_basics, principals->tconst );
      printf( "%s\n", title->primaryTitle );
    } else if (strcmp(first, "title") == 0) {
      title = find_primary_title (title_basics, second);
      principals = find_principals_tconst(title_principals, title->tconst);
      name = find_primary_name (name_basics, principals->nconst);
      printf( "%s\n", name->primaryName );
    }
  }


  /*title_basics = get_title( argv[1] );

  build_ptindex( title_basics );

  build_tindex( title_basics );

  printf("lines: %d\n", title_basics->num);

  name_basics = get_name( argv[1] );


  build_pnindex( name_basics );

  build_nindex( name_basics );

  printf("lines: %d\n", name_basics->num);

  title_principals = get_principals( argv[1] );


  build_pntindex( title_principals );

  build_pncindex( title_principals );

  printf("lines: %d\n", title_principals->num);


  printf( "Ready\n" );

  name = find_primary_name( name_basics, "Bruce Lee" );

  principals = find_principals_nconst( title_principals, name->nconst );

  title = find_tconst( title_basics, principals->tconst );

  printf( "%s\n", title->primaryTitle );*/

  return 0;
}
