#include "ecdhe.h"
#include "ecpoint.h"
#include "fp.h"

int main(int, char**) {
  Fp::init("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
  ECPoint::init();
  ECPoint a = ECPoint(mpz_class(ES_ECC_X), mpz_class(ES_ECC_Y));
  std::cout << a << std::endl;
}
