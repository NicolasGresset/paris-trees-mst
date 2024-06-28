#include <stdio.h>
#include <stdlib.h>

/**
A convenient way to handle errors : will call raler if condition is true
--> means bad return code
 */
#define CHK(condition)                                                                \
  do {                                                                         \
    if (condition)                                                            \
      raler(#condition, __FILE__, __LINE__);                                          \
  } while (0);

void raler(const char *msg, const char *file, int line);