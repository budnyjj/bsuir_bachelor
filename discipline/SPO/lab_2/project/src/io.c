#include "io.h"

void clear_input() {
  while (getchar() != '\n');
}

void error(char* msg) {
  printf("%s\n", msg);
}
