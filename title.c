#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "title.h"
#include "common.h"
#include "binary.h"

struct title_basics_array* get_title(char * path) {
  FILE *fp;
  char line[1056];
  char type[256];
  char adlt[256];
  char title[256];
  char tcon[256];
  int count = 0;
  int i = 0;
  struct title_basics_array* titles = malloc (sizeof (struct title_basics_array));
  int len = strlen(path) + strlen("/title.basics.tsv") + 1;
  char *fullpath = malloc(len);
  strcpy(fullpath, path);
  strcat(fullpath, "/title.basics.tsv\0");
  fp = fopen(fullpath, "r");

  while (fgets(line, 1056, fp)) {
    get_column(line, type, 1);
    get_column(line, adlt, 4);
    if (strstr(type, "movie") && strstr(adlt, "0"))
    {
      count++;
    }
  }

  fseek(fp, 0, SEEK_SET);
  titles->titles = malloc(sizeof(struct title_basics) * count);
  titles->num = count;

  while (fgets(line, 1056, fp)) {
    get_column(line, type, 1);
    get_column(line, adlt, 4);
    if (strstr(type, "movie") && strstr(adlt, "0"))
    {
      get_column(line, tcon, 0);
      get_column(line, title, 2);
      titles->titles[i].tconst = malloc(strlen(tcon) + 1);
      strcpy(titles->titles[i].tconst, tcon);
      titles->titles[i].primaryTitle = malloc(strlen(title) + 1);
      strcpy(titles->titles[i].primaryTitle, title);
      i++;
    }
  }

  titles->tconst_tree = 0;
  titles->primaryTitle_tree = 0;

  return titles;
}

void build_ptindex( struct title_basics_array* titles ) {
  int i;
  struct node *tree = NULL;
  tree = add_node(tree, titles->titles[0].primaryTitle, &(titles->titles[0]));
  for (i = 1; i < titles->num; i++) {
    add_node(tree, titles->titles[i].primaryTitle, &(titles->titles[i]));
  }
  titles->primaryTitle_tree = tree;
}

struct title_basics * find_primary_title (struct title_basics_array* titles, char *key) {
  struct node* tree = find_node(titles->primaryTitle_tree, key);
  if (tree) {
    return tree->data;
  }
  return NULL;
}
