#include "test.h"

static int st_err = 0, st_test = 0;

void test_ecc_point() {
  ECPoint P(mpz_class("0x8692fc91a13aecdd636563f4d57065826475fe16a070e436a384fd465c22a590"), mpz_class("0xec90f12d63ea8e616afcb7088d2bf7bee7211b59b254839c79815c3da7f1ca54"));
  ECPoint Q(mpz_class("0xc6045a989183a6493c85c2d925ae46eecf7e4760c8c7a0a2a611fecf54f7719e"), mpz_class("0xdac1c37ff7b22f4b0f7889e2275d541a0c06cde44b55891f4f1dca86914659c5"));
  ES_ASSERT_EQ(ECPoint::isPointOnECC(mpz_class(ES_ECC_X), mpz_class(ES_ECC_Y)), true);
  ES_ASSERT_EQ(ECPoint::isPointOnECC(0, 1), false);
  ES_ASSERT_EQ(P+Q, ECPoint(
        mpz_class("98520248413506909800951464424767143162018370521327345505766116972348589848344"),
        mpz_class("3545839799967974179505581531658653562100449522461009153640445279701593785652"))
 );
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
