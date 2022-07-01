#include "s21_grep.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    printf("\nargv[%d] \t = %s\t length = %ld\n", i, argv[i], strlen(argv[i]));
  }
  int error_flags = 1;
  grep_flags flags;
  init_flags(&flags);
  for (int i = 0; i < argc; i++) {
    if (*argv[i] == '-')
      if (strlen(argv[i]) >= 2) {
        argv[i]++;
        error_flags = check_flags(argv[i], &flags);
      }
  }
  // функция проверки зависимостей проверяет условия

  return (0);
}

void init_flags(grep_flags* flags) {
  flags->flag_e = 1;
  flags->flag_i = 0;
  flags->flag_v = 0;
  flags->flag_c = 0;
  flags->flag_l = 0;
  flags->flag_n = 0;
  flags->flag_h = 0;
  flags->flag_s = 0;
  flags->flag_f = 0;
  flags->flag_o = 0;
}

int check_flags(char* argv, grep_flags* flags) {
  int result = 1;
  for (int i = 0; i < strlen(argv); i++) {
    if (argv[i] == 'e')
      continue;
    else if (argv[i] == 'i')
      flags->flag_i = 1;
    else if (argv[i] == 'v')
      flags->flag_v = 1;
    else if (argv[i] == 'c')
      flags->flag_c = 1;
    else if (argv[i] == 'l')
      flags->flag_l = 1;
    else if (argv[i] == 'n')
      flags->flag_n = 1;
    else if (argv[i] == 'h')
      flags->flag_h = 1;
    else if (argv[i] == 's')
      flags->flag_s = 1;
    else if (argv[i] == 'f')
      flags->flag_f = 1;
    else if (argv[i] == 'o')
      flags->flag_o = 1;
    else
      result = 0;
  }
  return result;
}