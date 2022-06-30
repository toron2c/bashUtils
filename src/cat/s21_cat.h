#ifndef _SRC_CAT_
#define _SRC_CAT_

typedef struct {
  int flag_v;  // 5
  int flag_b;  //нумерует непустые строки 3
  int flag_e;  // отображает символы конца строки знаком $ 4
  int flag_n;  //нумерует все строки 2
  int flag_s;  // сжимает несколько смежных пустых строк // 1
  int flag_t;  // 6
} info_flags;

int check_flags(char *str, info_flags *t_flags);
int check_fullname_flags(char *str, info_flags *t_flags);

void init_flags(info_flags *t_flags);  // инициализация структуры

int get_size_file(char *src);

void action_flags(char *str, char *prev_str, int counter, info_flags t_flags);

int action_flag_s(char *str, char *prev_str);

void action_flag_n(char *str, int counter);

void *s21_insert(const char *src, const char *str, int start_index);

void read_file(char *src, int size, info_flags t_flags);

#endif  // _SRC_CAT_