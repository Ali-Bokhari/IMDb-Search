#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "principals.h"
#include "common.h"

struct title_principals_array* get_principal(char * path) {
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
      strcpy(principals->principals[i].nconst, ncon);
      principals->principals[i].tconst = malloc(strlen(tcon) + 1);
      strcpy(principals->principals[i].tconst, tcon);
      principals->principals[i].characters = malloc(strlen(chars) + 1);
      strcpy(principals->principals[i].characters, chars);
      i++;
    }
  }

  principals->tconst_tree = 0;
  principals->nconst_tree = 0;

  return principals;
}
