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

void read_file(char *src, info_flags t_flags);

void write_symbol_end();

int check_flag_e(char c);

int check_flag_t(char c);

void write_symbol_tab();

int action_flag_s(char prev_c, char prev_prev_c, char current_c);

void action_flag_n(char *str, int counter);

int action_flag_b(char current, char prev);

int check_start_line(char c, char prev_c, int *counter_line,
                     int *counter_without_void);

void write_number_line(int counter);

void *s21_insert(const char *src, const char *str, int start_index);

#endif  // _SRC_CAT_