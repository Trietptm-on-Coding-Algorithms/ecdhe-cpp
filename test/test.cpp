#include "test.h"

static int st_err = 0, st_test = 0;

void test_ecc_point() {
  Fp::init("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
  ECPoint P(Fp("0x104793ff3eca884f3214de11e39d5335d86d27cc126622c26a3ec9e8bfa079"), Fp("0x3bb3614644928b2d7c287ae2e40c6058fc517f8322737db406a816fde702602f"));
  ECPoint Q(Fp("0x28116cf661b0b8806e100194ed935d9507b0b8c8b02f7327d1ee2df8974c0"), Fp("0xc585109a622f2062a4e8f7110ffc7fc9970720bb6beead10ab63c2893fccab76"));
  ECPoint R(Fp("0x1df3fbe33b5c40f47cf1311bcb9cd40efdb7f669fa4af08ce6e5200cf611ff0"), Fp("0x456b16bc9349d94f4d07e3130e659a41d1eb2a566294d54c526d25ec100be2e8"));
  ECPoint S(Fp("28920512013152058348856411929490711080171777685383490337594993447826326857285"), Fp("11179493115481685824005416855047781305068775593233996421482812460240583939963"));
  ECPoint T(Fp("70848489326787443623343009379527957094449797063111572948408238826727828087934"), Fp("13987853872617742633474627483207765316351761861433003533695188499096480257210"));

  ES_ASSERT_EQ(ECPoint::isPointOnECC(Fp(ES_ECC_X), Fp(ES_ECC_Y)), true);
  ES_ASSERT_EQ(ECPoint::isPointOnECC(Fp(0), Fp(1)), false);
  ES_ASSERT_EQ(P+Q, ECPoint(Fp("0xf9c603cbe59cef943f5adff0f358cd290603a8d53168ec36debaa50c1263971e"), Fp("0xf26a460469711b4d1f7e37073cfeb73f2b86a5570ff1c261be6c21ec9ca7c40f")));
  ES_ASSERT_EQ(R+R, S);
  ES_ASSERT_EQ(R*2, S);
  ES_ASSERT_EQ(R*24,T);
}

void test_fp() {
  Fp::init("7");
  Fp a(0), b(5), c(20), d(256);
  ES_ASSERT_EQ(a, 0);
  ES_ASSERT_EQ(d, Fp(4));
  ES_ASSERT_EQ(b, Fp(5));
  ES_ASSERT_EQ(c, Fp(6));
  ES_ASSERT_EQ(a+b, Fp(5));
  ES_ASSERT_EQ(a-b, Fp(2));
  ES_ASSERT_EQ(a*b, Fp(0));
  ES_ASSERT_EQ(b*c, Fp(2));
  ES_ASSERT_EQ(b-c*b, Fp(3));
  ES_ASSERT_EQ(d/b, Fp(5));
  ES_ASSERT_EQ(b+c-d, Fp(0));
  ES_ASSERT_EQ(Fp(-3), Fp(4));
}

void exec_test() {
  test_fp();
  test_ecc_point();
  printf("[+] Tested %d tests.\n", st_test);
  if(st_err) {
    printf("[+] %d error(s) found.\n", st_err);
  }
}

int main() {
  ECPoint::init();
  exec_test();
}
