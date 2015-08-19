#include "test.h"

static int st_err = 0, st_test = 0;

void test_ecc_point() {
  ECPoint P(Fp("0x104793ff3eca884f3214de11e39d5335d86d27cc126622c26a3ec9e8bfa079"), Fp("0x3bb3614644928b2d7c287ae2e40c6058fc517f8322737db406a816fde702602f"));
  ECPoint Q(Fp("0x28116cf661b0b8806e100194ed935d9507b0b8c8b02f7327d1ee2df8974c0"), Fp("0xc585109a622f2062a4e8f7110ffc7fc9970720bb6beead10ab63c2893fccab76"));

  ES_ASSERT_EQ(ECPoint::isPointOnECC(Fp(ES_ECC_X), Fp(ES_ECC_Y)), true);
  ES_ASSERT_EQ(ECPoint::isPointOnECC(Fp(0), Fp(1)), false);
  ES_ASSERT_EQ(P+Q, ECPoint(Fp("0xf9c603cbe59cef943f5adff0f358cd290603a8d53168ec36debaa50c1263971e"), Fp("0xf26a460469711b4d1f7e37073cfeb73f2b86a5570ff1c261be6c21ec9ca7c40f")));
}

void exec_test() {
  test_ecc_point();
  printf("[+] Tested %d tests.\n", st_test);
  if(st_err) {
    printf("[+] %d error(s) found.\n", st_err);
  }
}

int main() {
  Fp::init("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
  ECPoint::init();
  exec_test();
}
