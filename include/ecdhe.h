#pragma once

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <gmpxx.h>

#define ES_ECC_X ("0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798")
#define ES_ECC_Y ("0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8")

extern const mpz_class secp256k1_p;
extern const mpz_class secp256k1_a;
extern const mpz_class secp256k1_b;

class ECPoint {
  private:
    mpz_class x, y;
  public:
    ECPoint(mpz_class _x, mpz_class _y);
    friend std::ostream& operator<<(std::ostream&, const ECPoint&);

    static bool isPointOnECC(mpz_class x, mpz_class y) {
      return (y * y) % secp256k1_p == (x*x*x + secp256k1_b) % secp256k1_p;
    }
};
