#pragma once

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <gmpxx.h>

class Fp {
  private:
    mpz_class x;
    static mpz_class p;
  public:
    static void init(const char *);

    friend Fp operator+(const Fp&, const Fp&);
    friend Fp operator-(const Fp&, const Fp&);
    friend Fp operator-(const Fp&);
    friend Fp operator*(const Fp&, const Fp&);
    friend Fp operator/(const Fp&, const Fp&);
    friend bool operator==(const Fp&, const Fp&);
    friend bool operator!=(const Fp&, const Fp&);
    friend std::ostream& operator<<(std::ostream&, const Fp&);

    Fp() : x(0) { }
    Fp(const mpz_class& _x) : x(_x % p) {
      if (_x < 0) {
        x = (_x + p) % p;
      }
    }
    Fp(const char *_x) {
      if (_x == 0) {
        x = 0;
      } else {
        x = mpz_class(_x) % p;
      }
    }
};

bool operator==(const Fp& me, const int rhs);
bool operator!=(const Fp& me, const int rhs);

Fp operator+=(Fp& me, const Fp& rhs);
Fp operator-=(Fp& me, const Fp& rhs);
Fp operator*=(Fp& me, const Fp& rhs);
Fp operator/=(Fp& me, const Fp& rhs);
