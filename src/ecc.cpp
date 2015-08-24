#include "ecpoint.h"
#include "fp.h"
#include <stdexcept>

mpz_class ECPoint::p;
mpz_class ECPoint::a;
mpz_class ECPoint::b;

void ECPoint::init() {
  p.set_str("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f", 16);
  a.set_str("0", 10);
  b.set_str("7", 10);
}

ECPoint::ECPoint(const Fp& _x, const Fp& _y) : x(), y(), infinity(false) {
  set(_x, _y);
}

void ECPoint::set(const Fp& _x, const Fp& _y) {
  if (!isPointOnECC(_x, _y) && !(_x == 0 && _y == 0)) {
    std::cerr << "Error: Point (" << _x << ", " << _y << ") is not point on this curve" << std::endl;
    throw std::runtime_error("Point is not point on this curve.");
  }
  x = _x;
  y = _y;
  infinity = (_x == 0 && _y == 0);
}

std::ostream& operator<<(std::ostream& _os, const ECPoint& rhs) {
  if (rhs.isInfinity()) {
    _os << "(Infinity)";
  } else {
    _os << "(" << rhs.x << ", " << rhs.y << ")";
  }
  return _os;
}

bool operator==(const ECPoint& me, const ECPoint& rhs) {
  return (me.x == rhs.x && me.y == rhs.y);
}

bool operator!=(const ECPoint& me, const ECPoint& rhs) {
  return !(me == rhs);
}

ECPoint operator+(const ECPoint& me, const ECPoint& rhs) {
  Fp x3(0), y3(0), l(0);

  if (rhs.isInfinity()) {
    return me;
  } else if (me.isInfinity()) {
    return rhs;
  }
  if (-me.y == rhs.y) {
    return ECPoint();
  }

  if (me.x != rhs.x) {
    l = (rhs.y - me.y) / (rhs.x - me.x);
  } else {
    l = (Fp(3)*me.x*me.x + me.a) / (Fp(2)*me.y);
  }

  x3 = (l*l - (me.x + rhs.x));
  y3 = (l*me.x - l*x3 - me.y);
  return ECPoint(x3, y3);
}

ECPoint operator-(const ECPoint& me, const ECPoint& rhs) {
  return me + -rhs;
}

ECPoint operator-(const ECPoint& me) {
  if (me.isInfinity()) {
    return me;
  }
  return ECPoint(me.x, -me.y);
}

ECPoint operator*(const ECPoint& me, const mpz_class& n) {
  mpz_class d = mpz_class(n);
  if (n == 1) {
    return me;
  } else if (n == 2) {
    return me + me;
  }
  ECPoint P = ECPoint(me);
  ECPoint ret;
  while(d != 0) {
    if ((d & 1) == 1) {
      ret = P + ret;
    }
    P = P + P;
    d >>= 1;
  }
  return ret;
}

ECPoint operator*(int n, const ECPoint& me) {
  return me * mpz_class(n);
}

ECPoint operator*(const mpz_class& n, const ECPoint& me) {
  return me * mpz_class(n);
}

ECPoint operator*(const ECPoint& me, int n) {
  return me * mpz_class(n);
}

bool ECPoint::isPointOnECC(const Fp& x, const Fp& y) {
  return (y * y) == (x*x*x + b);
}
