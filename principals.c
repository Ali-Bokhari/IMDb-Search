#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "principals.h"
#include "common.h"
#include "binary.h"

struct title_principals_array* get_principals(char * path) {
  FILE *fp;
  char line[2048];
  char colm[256];
  char chars[256];
  char ncon[256];
  char tcon[256];
  int count = 0;
  int i = 0;
  struct title_principals_array* principals = malloc (sizeof (struct title_principals_array));
  int len = strlen(path) + strlen("/title.principals.tsv") + 1;
  char *fullpath = malloc(len);
  strcpy(fullpath, path);
  strcat(fullpath, "/title.principals.tsv\0");
  fp = fopen(fullpath, "r");

  while (fgets(line, 2048, fp)) {
    get_column(line, colm, 3);
    if (strstr(colm, "actor") || strstr(colm, "actress"))
    {
      count++;
    }
  }

  fseek(fp, 0, SEEK_SET);
  principals->principals = malloc(sizeof(struct title_principals) * count);
  principals->num = count;

  while (fgets(line, 2048, fp)) {
    get_column(line, colm, 3);
    if (strstr(colm, "actor") || strstr(colm, "actress"))
    {
      get_column(line, tcon, 0);
      get_column(line, ncon, 2);
      get_column(line, chars, 5);
      principals->principals[i].nconst = malloc(strlen(ncon) + 1);
      strcpy(principals->principals[i].nconst, reverse(ncon));
      principals->principals[i].tconst = malloc(strlen(tcon) + 1);
      strcpy(principals->principals[i].tconst, reverse(tcon));
      principals->principals[i].characters = malloc(strlen(chars) + 1);
      strcpy(principals->principals[i].characters, chars);
      i++;
    }
  }

  principals->tconst_tree = 0;
  principals->nconst_tree = 0;

  return principals;
}

void build_pncindex( struct title_principals_array* principals ) {
  int i;
  struct node *tree = NULL;
  tree = add_node(tree, principals->principals[0].nconst, &(principals->principals[0]));
  for (i = 1; i < principals->num; i++) {
    add_node(tree, principals->principals[i].nconst, &(principals->principals[i]));
  }
  principals->nconst_tree = tree;
}

struct title_principals * find_principals_nconst (struct title_principals_array* principals, char *key) {
  struct node* tree = find_node(principals->nconst_tree, key);
  if (tree) {
    return tree->data;
  }
  return NULL;
}

void build_pntindex( struct title_principals_array* principals ) {
  int i;
  struct node *tree = NULL;
  tree = add_node(tree, principals->principals[0].tconst, &(principals->principals[0]));
  for (i = 1; i < principals->num; i++) {
    add_node(tree, principals->principals[i].tconst, &(principals->principals[i]));
  }
  principals->tconst_tree = tree;
}

struct title_principals * find_principals_tconst (struct title_principals_array* principals, char *key) {
  struct node* tree = find_node(principals->tconst_tree, key);
  if (tree) {
    return tree->data;
  }
  return NULL;
}
