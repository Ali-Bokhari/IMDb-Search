#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "name.h"
#include "common.h"

struct name_basics* getName(char * path) {
  FILE *fp;
  char line[256];
  char colm[256];
  int count = 0;
  int len = strlen(path) + strlen("/name.basics.tsv") + 1;
  char *fullpath = malloc(len);
  strcpy(fullpath, path);
  strcat(fullpath, "/name.basics.tsv");
  fp = fopen(fullpath, "r");

  while (fgets(line, 256, fp)) {
    get_column(line, colm, 4);
    if (strstr(colm, "actor") || strstr(colm, "actress"))
    {
      count++;
    }
  }
  printf("lines: %d\n", count);
  return NULL;
}
