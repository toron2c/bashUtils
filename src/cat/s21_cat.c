#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[]) {
  for (int i = 0; i < argc; i++) {
    printf("\nargv[%d] \t = %s\t length = %ld\n", i, argv[i], strlen(argv[i]));
  }
  int error_flags =
      1;  // 1 - нет ошибок, 0 ошибка, прерывание программы, не читать файл

  info_flags t_flags;
  init_flags(&t_flags);
  for (int i = 0; i < argc; i++) {
    if (*argv[i] == '-') {
      if (strlen(argv[i]) >= 2) {
        if (*++argv[i] == '-') {
          argv[i]++;
          error_flags = check_fullname_flags(argv[i], &t_flags);
        } else {
          error_flags = check_flags(argv[i], &t_flags);
        }
      }
    }
  }
  int size = 0;
  FILE* fp;
  if (error_flags == 1) {
    for (int i = 1; i < argc; i++) {
      size = get_size_file(argv[i]);
      if (size > 0) {
        read_file(argv[i], t_flags);
      }
    }
  }
  printf("%d - size\n", size);
  // fp = fopen(argv[3], "r");
  // char* tmp_str = calloc(size, sizeof(char));

  // // блок кода считающий общее количество символов в файле, будет
  // повторяться,
  // // возможно следует вынести в src/common
  // // скорее всего так же будет проверять аргумент на то файл это или нет

  // fseek(fp, 0, SEEK_END);

  // int sz = ftell(fp);

  // printf("\n%d\n", sz);

  // fseek(fp, 0, SEEK_SET);
  // ==

  // char string[5000];
  // int i;
  // while ((string[i] = fgetc(fp)) != EOF) {
  //   if (string[i] == '\n') {
  //     string[i] = '\0';
  //     printf("%s\n", string);
  //     i = 0;
  //   } else
  //     i++;
  // }
  return argc;
}

int check_fullname_flags(char* str, info_flags* t_flags) {
  int result = 1;
  if ((strcmp(str, "number-nonblank")) == 0) {
    t_flags->flag_b = 1;
  } else if ((strcmp(str, "number")) == 0) {
    t_flags->flag_n = 1;
  } else if ((strcmp(str, "show-ends")) == 0) {
    t_flags->flag_e = 1;
  } else if ((strcmp(str, "squeeze-blank")) == 0) {
    t_flags->flag_s = 1;
  } else if ((strcmp(str, "show-tabs")) == 0) {
    t_flags->flag_t = 1;
  } else if ((strcmp(str, "show-nonprinting")) == 0) {
    t_flags->flag_v = 1;
  } else {
    result = 0;
  }
  return result;
}

int check_flags(char* str, info_flags* t_flags) {
  int result = 1;
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == 'v') {
      t_flags->flag_v = 1;
    } else if (str[i] == 'b') {
      t_flags->flag_b = 1;
    } else if (str[i] == 'e') {
      t_flags->flag_e = 1;
      t_flags->flag_v = 1;
    } else if (str[i] == 'n') {
      t_flags->flag_n = 1;
    } else if (str[i] == 's') {
      t_flags->flag_s = 1;
    } else if (str[i] == 't') {
      t_flags->flag_t = 1;
      t_flags->flag_v = 1;
    } else if (str[i] == 'T') {
      t_flags->flag_t = 1;
    } else if (str[i] == 'E') {
      t_flags->flag_e = 1;
    } else {
      result = 0;
      break;
    }
  }
  return result;
}

void init_flags(info_flags* t_flags) {
  t_flags->flag_b = 0;
  t_flags->flag_e = 0;
  t_flags->flag_v = 0;
  t_flags->flag_n = 0;
  t_flags->flag_s = 0;
  t_flags->flag_t = 0;
}

void action_flag_e(char* str) {
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == '\n') {
      str[i] = '$';
      str[i + 1] = '\n';
    }
  }
}

int get_size_file(char* src) {
  int size = 0;
  FILE* file = fopen(src, "r");
  if (file != NULL) {
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
  }
  return size;
}

void read_file(char* src, info_flags t_flags) {
  FILE* file = fopen(src, "r");
  char prev_c = ' ';
  char prev_prev_c = ' ';
  char current_c;
  int counter_line = 1;
  int start_line = -1;
  int counter_without_void = 1;
  while ((current_c = fgetc(file)) != EOF) {
    if ((t_flags.flag_s) && (action_flag_s(prev_c, prev_prev_c, current_c))) {
      continue;
    }
    if ((t_flags.flag_n && start_line) ||
        ((t_flags.flag_n == 1) && (start_line == -1))) {
      write_number_line(counter_line);
    }

    if ((t_flags.flag_b) && (action_flag_b(current_c, prev_c))) {
      if (start_line) write_number_line(counter_without_void);
    }
    if ((t_flags.flag_e) && check_flag_e(current_c)) wryte_symbol_end();
    printf("%c", current_c);
    prev_prev_c = prev_c;
    prev_c = current_c;

    start_line = check_start_line(prev_c, prev_prev_c, &counter_line,
                                  &counter_without_void);
  }
}

int action_flag_s(char prev_c, char prev_prev_c, char current_c) {
  int flag = 0;
  if (prev_c == '\n' && prev_prev_c == '\n' && current_c == '\n') {
    flag = 1;
  }
  return flag;
}

int check_start_line(char c, char prev_c, int* counter_line,
                     int* counter_without_void) {
  int flag = 0;
  if (c == '\n') {
    flag = 1;
    *counter_line = *counter_line + 1;
    if (prev_c != '\n') *counter_without_void = *counter_without_void + 1;
  }
  return flag;
}

int action_flag_b(char current, char prev) {
  int flag = 1;
  if ((current == '\n') && (prev == '\n')) {
    flag = 0;
  }
  return flag;
}

void write_number_line(int counter) { printf("%6d\t", counter); }

void wryte_symbol_end() { printf("$"); }

int check_flag_e(char c) {
  int flag = 0;
  if (c == '\n') flag = 1;
  return flag;
}
