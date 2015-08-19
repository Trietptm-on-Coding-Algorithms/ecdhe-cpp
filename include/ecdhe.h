#pragma once

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <gmpxx.h>

const char ES_ECC_X[] = "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";
const char ES_ECC_Y[] = "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";

class ECPoint {
  private:
    static mpz_class p;
    static mpz_class a;
    static mpz_class b;

    mpz_class x, y;
  public:
    static void init();
    ECPoint(mpz_class _x, mpz_class _y);
    bool operator==(const ECPoint& other);
    bool operator!=(const ECPoint& other);
    ECPoint operator+(const ECPoint& other);
    /*
    ECPoint operator-(const ECPoint& other);
    ECPoint operator*(const mpz_class& other);
    ECPoint inverse();
    */
    friend std::ostream& operator<<(std::ostream&, const ECPoint&);

    static bool isPointOnECC(mpz_class x, mpz_class y);
};
