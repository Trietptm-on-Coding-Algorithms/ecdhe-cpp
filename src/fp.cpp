#include "ecdhe.h"
#include "fp.h"
#include <stdexcept>
#include <assert.h>

mpz_class Fp::p;

inline void invMod(mpz_class& z, const mpz_class& x, const mpz_class& m) {
  assert(m != 0);
  mpz_invert(z.get_mpz_t(), x.get_mpz_t(), m.get_mpz_t());
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
  mpz_class c(me.x - rhs.x);
  if (c < 0) {
    c += Fp::p;
  }
  return Fp(c);
}
Fp operator-(const Fp& me) {
  return Fp(-me.x) + Fp::p;
}
Fp operator*(const Fp& me, const Fp& rhs) {
  return Fp(me.x * rhs.x);
}
Fp operator/(const Fp& me, const Fp& rhs) { 
  mpz_class c(rhs.x);
  invMod(c, rhs.x, Fp::p);
  return me * c;
}

bool operator!=(const Fp& me, const Fp& rhs) {
  return !(me == rhs);
}
bool operator==(const Fp& me, const Fp& rhs) {
  return me.x == rhs.x;
}

std::ostream& operator<<(std::ostream& os, const Fp& rhs) {
  os << rhs.x;
  return os;
}
Fp operator+=(Fp& me, const Fp& rhs) {
  me = me + rhs;
  return me;
}
Fp operator-=(Fp& me, const Fp& rhs) {
  me = me - rhs;
  return me;
}
Fp operator*=(Fp& me, const Fp& rhs) {
  me = me * rhs;
  return me;
}
Fp operator/=(Fp& me, const Fp& rhs) {
  me = me / rhs;
  return me;
}
