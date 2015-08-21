#include <fstream>
#include "ecdhe.h"
#include "ecpoint.h"
#include "fp.h"

int main(int, char**) {
  Fp::init("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
  ECPoint::init();
  ECPoint G = ECPoint(mpz_class(ES_ECC_X), mpz_class(ES_ECC_Y));
  srand(time(0));
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
