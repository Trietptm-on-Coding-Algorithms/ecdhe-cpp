#include "test.h"

static int st_err = 0, st_test = 0;

void exec_test() {
  printf("[+] Tested %d tests.\n", st_test);
  if(st_err) {
    printf("[+] %d error(s) found.\n", st_err);
  }
}

int main() {
  exec_test();
}
