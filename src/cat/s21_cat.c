#include "s21_cat.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    printf("\nargv[%d] \t = %s", i, argv[i]);
  }
  FILE* fp;
  fp = fopen(argv[2], "r");
  char string[5000];
  int i;
  while ((string[i] = fgetc(fp)) != EOF) {
    if (string[i] == '\n') {
      string[i] = '$';
      string[i + 1] = '\0';
      printf("%s\n", string);
      i = 0;
    } else
      i++;
  }
  return argc;
}
