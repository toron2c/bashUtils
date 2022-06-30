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
        read_file(argv[i], size, t_flags);
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

void read_file(char* src, int size, info_flags t_flags) {
  FILE* file = fopen(src, "r");
  char* str = calloc(size + 1, sizeof(char));
  char* prev_str = calloc(size + 1, sizeof(char));
  int counter_line = 1;
  for (int i = 0; str[i] = fgetc(file) != EOF; i++) {
    if (str[i] == '\n') {
      action_flags(str, prev_str, counter_line, t_flags);
      strcpy(prev_str, str);
      i = 0;
    }
  }
}

void action_flags(char* str, char* prev_str, int counter, info_flags t_flags) {
  int flag_no_print = 0;
  printf("%s\n%s\n", str, prev_str);
  if ((t_flags.flag_s) && (action_flag_s(str, prev_str))) {
    flag_no_print = 1;
    printf("-stroka\n");
  }
}

int action_flag_s(char* str, char* prev_str) {
  int flag = 0;

  if (prev_str[0] == '\n' && str[0] == '\n') {
    flag = 1;
  }
  return flag;
}
void action_flag_n(char* str, int counter) {
  char* p_this_counter = calloc(10, sizeof(char));
  sprintf(p_this_counter, "%d\t", counter);
  char* new_str = s21_insert(str, p_this_counter, 0);
  strcpy(str, new_str);
  free(p_this_counter);
  free(new_str);
}

void* s21_insert(const char* src, const char* str, int start_index) {
  int length_src = strlen(src);
  int length_str = strlen(str);
  int i = 0;
  char* new_string = calloc(length_src + length_str + 1, sizeof(char));
  int indx_str = 0;
  if (new_string) {
    for (; i < length_src + length_str; i++) {
      if (i == start_index) {
        strcat(new_string, str);
        i += length_str - 1;
        continue;
      }
      new_string[i] = src[indx_str];
      indx_str++;
    }
    new_string[i] = '\0';
  }
  return new_string;
}
