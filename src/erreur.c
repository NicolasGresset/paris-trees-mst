#include "../include/erreur.h"
#include <stdlib.h>

void raler(const char *msg, const char *file, int line) {
  fprintf(stderr, "%s:%d:", file, line);
  perror(msg);
  exit(EXIT_FAILURE);
}