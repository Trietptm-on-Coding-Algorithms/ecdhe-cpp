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

  public:
    Fp x, y;
    static void init();
    ECPoint(const Fp& _x, const Fp& _y);
    bool operator==(const ECPoint& other) const;
    bool operator!=(const ECPoint& other) const;
    ECPoint operator+(const ECPoint& other) const;
    friend std::ostream& operator<<(std::ostream&, const ECPoint&);

    static bool isPointOnECC(const Fp& x, const Fp& y);
};
