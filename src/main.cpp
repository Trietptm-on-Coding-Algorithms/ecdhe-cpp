#include "ecdhe.h"

int main(int, char**) {
  ECPoint a(mpz_class(ES_ECC_X), mpz_class(ES_ECC_Y));
  std::cout << a << std::endl;
}
