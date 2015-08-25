#include <fstream>
#include "ecdhe.h"
#include "ecpoint.h"
#include "fp.h"

#define ES_TIME_TEST(init, x) do {\
  std::cout << "Start (" << #x << ")... " << std::endl; \
  init; \
  start = clock(); \
  for (int i = 0; i < CYCLE; i++) { x; } \
  end = clock(); \
  std::cout << "\tFinished." << std::endl << "Time: " << ((double)end - start)/CLOCKS_PER_SEC/CYCLE * 1e+6 << "usec" << std::endl; \
} while (0)


void ecdhe_test() {
  ECPoint G = ECPoint(ES_ECC_X, ES_ECC_Y);
  mpz_class a = get_random_bytes(1024);
  std::cout << "a = " << a << std::endl;

  mpz_class b = get_random_bytes(1024);
  std::cout << "b = " << b << std::endl;

  ECPoint kA = a*G;
  std::cout << "kA = " << kA << std::endl;

  ECPoint kB = b*G;
  std::cout << "kB = " << kB << std::endl;

  ECPoint secret_A = kA * b;
  std::cout << "secret_A = " << secret_A << std::endl;

  ECPoint secret_B = kB * a;
  std::cout << "secret_B = " << secret_B << std::endl;

  std::cout << "secret_A == secret_B -> ";
  if (secret_A == secret_B) {
    std::cout << "true";
  } else {
    std::cout << "false";
  }
  std::cout << std::endl;
}

int main(int, char**) {
  Fp::init("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
  ECPoint::init();
  ECPoint G;
  clock_t start, end;
  constexpr int CYCLE = 1000000;
  Fp p, q;

  ES_TIME_TEST(p = Fp(0xdeadbeef), p += p);
  ES_TIME_TEST(p = Fp(0xdeadbeef), p -= p);
  ES_TIME_TEST(p = Fp(0xdeadbeef), p *= p);
  ES_TIME_TEST(p = Fp(0xdeadbeef); q = Fp(0xcafebabe), p += q);
  ES_TIME_TEST(p = Fp(0xdeadbeef); q = Fp(0xcafebabe), p -= q);
  ES_TIME_TEST(p = Fp(0xdeadbeef); q = Fp(0xcafebabe), p *= q);
  ES_TIME_TEST(p = Fp(0xdeadbeef); q = Fp(0xcafebabe), p /= q);
  ES_TIME_TEST(G = ECPoint(ES_ECC_X, ES_ECC_Y), G *= 1);
  ES_TIME_TEST(G = ECPoint(ES_ECC_X, ES_ECC_Y), G *= 2);
  /*
  ES_TIME_TEST(G = ECPoint(ES_ECC_X, ES_ECC_Y), G *= 3);
  ES_TIME_TEST(G = ECPoint(ES_ECC_X, ES_ECC_Y), G *= 4);
  ES_TIME_TEST(G = ECPoint(ES_ECC_X, ES_ECC_Y), G *= 32);
  ES_TIME_TEST(,ecdhe_test());*/
}
