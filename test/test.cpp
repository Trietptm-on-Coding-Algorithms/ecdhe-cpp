#include "test.h"

static int st_err = 0, st_test = 0;

void test_ecc_point() {
  ES_ASSERT_EQ(ECPoint::isPointOnECC(mpz_class(ES_ECC_X), mpz_class(ES_ECC_Y)), true);
  ES_ASSERT_EQ(ECPoint::isPointOnECC(200, 1), false);
}

void exec_test() {
  test_ecc_point();
  printf("[+] Tested %d tests.\n", st_test);
  if(st_err) {
    printf("[+] %d error(s) found.\n", st_err);
  }
}

int main() {
  exec_test();
}
