#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "name.h"
#include "common.h"
#include "title.h"
#include "principals.h"
#include "binary.h"

void printing_name(struct node *tree, struct name_basics_array *name, char* tconstt) {
  struct name_basics *nameb;
  if (!tree) {
    return;
  }
  if (strcmp (tconstt, ((struct title_principals*)tree->data)->tconst) == 0) {
    nameb = find_nconst (name, ((struct title_principals*)tree->data)->nconst);
    if (nameb) {
      printf( "%s : %s]\n", nameb->primaryName, ((struct title_principals*)tree->data)->characters );
    }
  }
  printing_name(tree->child[0], name, tconstt);
  printing_name(tree->child[1], name, tconstt);
}

void printing_title(struct node *tree, struct title_basics_array *title, char* nconstt) {
  struct title_basics *titleb;
  if (!tree) {
    return;
  }
  if (strcmp (nconstt, ((struct title_principals*)tree->data)->nconst) == 0) {
    titleb = find_tconst (title, ((struct title_principals*)tree->data)->tconst);
    if (titleb) {
      printf( "%s : %s]\n", titleb->primaryTitle, ((struct title_principals*)tree->data)->characters );
    }
  }
  printing_title(tree->child[0], title, nconstt);
  printing_title(tree->child[1], title, nconstt);
}


int main(int argc, char * argv[]) {
  struct title_basics_array *title_basics;
  struct title_basics *title;
  struct name_basics_array *name_basics;
  struct name_basics *name;
  struct title_principals_array *title_principals;
  /*struct title_principals *principals;*/
  char first[10];
  char second[256];
  int command;
  if (argc != 2) {
    fprintf( stderr, "Usage:  %s directory\n", argv[0] );
    exit(-1);
  }

  title_basics = get_title( argv[1] );

  build_ptindex( title_basics );

  build_tindex( title_basics );

  name_basics = get_name( argv[1] );


  build_pnindex( name_basics );

  build_nindex( name_basics );

  title_principals = get_principals( argv[1] );


  build_pntindex( title_principals );

  build_pncindex( title_principals );

  while (1) {
    printf("> ");
    scanf("%s ", first);
    fgets(second, 256, stdin);
    for (command = strlen(second)-1; isspace(second[command]); command--);
    second[command + 1] = '\0';
    
    if (strcmp(first, "name") == 0) {
      name = find_primary_name( name_basics, second );
      if(!name){continue;}
      printing_title(find_node(title_principals->nconst_tree, name->nconst), title_basics, name->nconst);
    } else if (strcmp(first, "title") == 0) {
      title = find_primary_title (title_basics, second);
      if(!title){continue;}
      printing_name(find_node(title_principals->tconst_tree, title->tconst), name_basics, title->tconst);
    }
  }
  return 0;
}
