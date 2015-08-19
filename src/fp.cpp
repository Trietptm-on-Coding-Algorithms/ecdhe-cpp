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
Fp Fp::operator+(const Fp& rhs) const {
  return Fp(x + rhs.x);
}
Fp Fp::operator-(const Fp& rhs) const {
  mpz_class c(x - rhs.x);
  if (c < 0) {
    c += p;
  }
  return Fp(c);
}

Fp Fp::operator*(const Fp& o) const {
  return Fp(x * o.x);
}

Fp Fp::operator/(const Fp& o) const { 
  mpz_class c(o.x);
  invMod(c, o.x, p);
  return *this * c;
}

bool Fp::operator!=(const Fp& o) const {
  return !(*this == o);
}

bool Fp::operator==(const Fp& o) const {
  return x == o.x;
}

std::ostream& operator<<(std::ostream& os, const Fp& o) {
  os << o.x;
  return os;
}
