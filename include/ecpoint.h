#pragma once

#include <iostream>
#include <cstddef>
#include <cstdlib>

#include <gmpxx.h>
#include "fp.h"

class ECPoint {
  private:
    static mpz_class p;
    static mpz_class a;
    static mpz_class b;
    bool infinity;

  public:
    Fp x, y;
    ECPoint(const Fp&, const Fp&);
    bool isInfinity();

    static void init();
    static bool isPointOnECC(const Fp&, const Fp&);

    friend bool operator==(const ECPoint&, const ECPoint&);
    friend bool operator!=(const ECPoint&, const ECPoint&);
    friend ECPoint operator+(const ECPoint&, const ECPoint&);
    friend ECPoint operator*(const ECPoint&, int);
    friend std::ostream& operator<<(std::ostream&, const ECPoint&);
};
