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
    Fp x, y;
    bool infinity;

  public:
    ECPoint(const Fp&, const Fp&);
    ECPoint() : x(0), y(0), infinity(true) { }

    bool isInfinity() const {
      return infinity;
    }

    void set(const Fp&, const Fp&);

    static void init();
    static bool isPointOnECC(const Fp&, const Fp&);

    friend bool operator==(const ECPoint&, const ECPoint&);
    friend bool operator!=(const ECPoint&, const ECPoint&);
    friend ECPoint operator+(const ECPoint&, const ECPoint&);
    friend ECPoint operator-(const ECPoint&, const ECPoint&);
    friend ECPoint operator*(const ECPoint&, const mpz_class&);
    friend std::ostream& operator<<(std::ostream&, const ECPoint&);
    friend ECPoint operator-(const ECPoint&);
};

ECPoint operator*(const ECPoint&, int);
ECPoint operator*(int, const ECPoint&);
ECPoint operator*(const mpz_class&, const ECPoint&);
ECPoint operator+=(ECPoint&, const ECPoint&);
ECPoint operator*=(ECPoint&, const mpz_class&);
