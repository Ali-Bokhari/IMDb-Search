#include <string.h>

void get_column (char *line, char* column, int cNum) {
  int one, two, tabs, i;
  tabs = 0;
  one = -1;
  two = -1;
  for (i = 0; line[i]; i++) {
    if (tabs == cNum && one == -1){
      one = i;
    }
    if (tabs == cNum + 1){
      two = i;
      break;
    }
    if(line[i] == '\t') {
      tabs++;
    }
  }
  if (two == -1) {
    two = strlen(line) - 1;
  }
  strncpy (column, &(line[one]), two-one-1);
  column[two-one-1] = '\0';
}

char *reverse(char *str) {
  char p;
  int i, j;
    if (!str || ! *str)
        return str;
    i = strlen(str) - 1;
    j = 0;
    while (i > j) {
        p = str[i];
        str[i] = str[j];
        str[j] = p;
        j++;
        i--;
    }
    return str;
}
