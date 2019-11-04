#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "name.h"
#include "common.h"
#include "binary.h"

struct name_basics_array* get_name(char * path) {
  FILE *fp;
  char line[256];
  char colm[256];
  char name[256];
  char ncon[256];
  int count = 0;
  int i = 0;
  struct name_basics_array* names = malloc (sizeof (struct name_basics_array));
  int len = strlen(path) + strlen("/name.basics.tsv") + 1;
  char *fullpath = malloc(len);
  strcpy(fullpath, path);
  strcat(fullpath, "/name.basics.tsv\0");
  fp = fopen(fullpath, "r");

  while (fgets(line, 256, fp)) {
    get_column(line, colm, 4);
    if (strstr(colm, "actor") || strstr(colm, "actress"))
    {
      count++;
    }
  }

  fseek(fp, 0, SEEK_SET);
  names->names = malloc(sizeof(struct name_basics) * count);
  names->num = count;

  while (fgets(line, 256, fp)) {
    get_column(line, colm, 4);
    if (strstr(colm, "actor") || strstr(colm, "actress"))
    {
      get_column(line, ncon, 0);
      get_column(line, name, 1);
      names->names[i].nconst = malloc(strlen(ncon) + 1);
      strcpy(names->names[i].nconst, ncon);
      names->names[i].primaryName = malloc(strlen(name) + 1);
      strcpy(names->names[i].primaryName, name);
      i++;
    }
  }

  names->nconst_tree = 0;
  names->primaryName_tree = 0;
  return names;
}

void build_pnindex( struct name_basics_array* names ) {
  int i;
  struct node *tree = NULL;
  tree = add_node(tree, names->names[0].primaryName, &(names->names[0]));
  for (i = 1; i < names->num; i++) {
    add_node(tree, names->names[i].primaryName, &(names->names[i]));
  }
  names->primaryName_tree = tree;
}

struct name_basics * find_primary_name (struct name_basics_array* names, char *key) {
  struct node* tree = find_node(names->primaryName_tree, key);
  if (tree) {
    return tree->data;
  }
  return NULL;
}
