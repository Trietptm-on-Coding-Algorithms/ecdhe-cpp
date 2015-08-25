#include "ecdhe.h"
#include "fp.h"
#include <stdexcept>
#include <assert.h>

mpz_class Fp::p;

inline void invMod(mpz_class& z, const mpz_class& x, const mpz_class& m) {
  if (m != 0) {
    mpz_invert(z.get_mpz_t(), x.get_mpz_t(), m.get_mpz_t());
  } else {
    throw std::runtime_error("Error: Divided by 0");
  }
}
void Fp::init(const char *prime) {
  p = mpz_class(prime);
  if (p <= 1) {
    throw std::runtime_error("not positive");
  }
}

Fp operator+(const Fp& me, const Fp& rhs) {
  return Fp(me.x + rhs.x);
}
Fp operator-(const Fp& me, const Fp& rhs) {
  mpz_class c = me.x - rhs.x;
  if (c > 0) {
    return c;
  }
    return Fp(c + Fp::p);
}
Fp operator-(const Fp& me) {
  return Fp(-me.x) + Fp::p;
}
Fp operator*(const Fp& me, const Fp& rhs) {
  return Fp(me.x * rhs.x);
}
Fp operator/(const Fp& me, const Fp& rhs) { 
  mpz_class c;
  invMod(c, rhs.x, Fp::p);
  return me * c;
}

bool operator==(const Fp& me, const int rhs){
  return me == Fp(rhs);
}
bool operator==(const Fp& me, const Fp& rhs) {
  return me.x == rhs.x;
}
bool operator!=(const Fp& me, const Fp& rhs) {
  return !(me == rhs);
}
bool operator!=(const Fp& me, const int rhs){
  return !(me == rhs);
}

std::ostream& operator<<(std::ostream& os, const Fp& rhs) {
  os << rhs.x;
  return os;
}
Fp& Fp::operator+=(const Fp& rhs) {
  x += rhs.x;
  if (x >= p) {
    x -= p;
  }
  return *this;
}
Fp& Fp::operator-=(const Fp& rhs) {
  x -= rhs.x;
  if (x < 0) {
    x += p;
  }
  return *this;
}
Fp& Fp::operator*=(const Fp& rhs) {
  x *= rhs.x;
  x %= p;
  return *this;
}
Fp& Fp::operator/=(const Fp& rhs) {
  mpz_class c;
  invMod(c, rhs.x, p);
  x *= c;
  x %= p;
  return *this;
}
