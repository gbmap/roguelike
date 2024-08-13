#include "u_str.h"

#include <stdlib.h>
#include <string.h>

const char *strcopy(const char *s) {
  char *ss = (char *)malloc(sizeof(char) * strlen(s));
  strcpy(ss, s);
  return ss;
}
