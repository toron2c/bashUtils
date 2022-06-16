#ifndef _SRC_CAT_
#define _SRC_CAT_

typedef struct {
  int flag_b;  //нумерует непустые строки
  int flag_e;  // отображает символы конца строки знаком $
  int flag_n;  //нумерует все строки
  int flag_s;  // сжимает несколько смежных пустых строк
  int flag_t;
} info_flags;

int check_flags(char *str, info_flags info_flags);

#endif  // _SRC_CAT_