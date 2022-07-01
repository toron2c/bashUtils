#ifndef _SRC_GREP_
#define _SRC_GREP_

typedef struct {
  int flag_e;  // ожидает шаблон для поиска
  int flag_i;  // игнорирует регистр
  int flag_v;  // исключает шаблон в поиске
  int flag_c;  // выводит количество совпадающих строк
  int flag_l;  // выводит строки без имени файла
  int flag_n;  // выводит также номер строки
  int flag_h;  // выводит найденые строки без имени файла
  int flag_s;  // не выводит ошибки о несуществующих или нечитаемых файлах
  int flag_f;  // получает регулярные выражения из файла
  int flag_o;  // печатает только совпадающие не пустые строки
} grep_flags;

void init_flags(grep_flags *flags);

int check_flags(char *argv, grep_flags *flags);

#endif  // _SRC_GREP_