#include <string.h>

void get_column (char *line, char* column, int cNum) {
  int one, two, tabs, i;
  tabs = 0;
  one = -1;
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
  strncpy (column, &(line[one]), two-one);
  column[two-one] = '\0';
}
