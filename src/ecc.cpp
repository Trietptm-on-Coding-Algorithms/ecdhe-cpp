#include "ecpoint.h"
#include "fp.h"

mpz_class ECPoint::p;
mpz_class ECPoint::a;
mpz_class ECPoint::b;

void ECPoint::init() {
  p.set_str("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f", 16);
  a.set_str("0", 10);
  b.set_str("7", 10);
}

ECPoint::ECPoint(const Fp& _x, const Fp& _y) : x(_x), y(_y) {
  if (!isPointOnECC(_x, _y)) {
    std::cerr << "Error: Point (" << _x << ", " << _y << ") is not point on this curve" << std::endl;
    exit(-1);
  }
}

std::ostream& operator<<(std::ostream& _os, const ECPoint& ptr) {
  _os << "(" << ptr.x << ", " << ptr.y << ")";
  return _os;
}

bool ECPoint::operator==(const ECPoint& other) const {
  return x == other.x && y == other.y;
}

bool ECPoint::operator!=(const ECPoint& other) const {
  return !(*this == other);
}

ECPoint ECPoint::operator+(const ECPoint& other) const {
  Fp x3(0), y3(0), l(0);

  if (x != other.x) {
    l = (other.y - y) / (other.x - x);
  } else {
    l = (Fp(3)*x*x + Fp(a)) / Fp(2)*y;
  }

  x3 = (l*l - (x + other.x));
  y3 = (l*x - l*x3 - y);
  return ECPoint(x3, y3);
}

ECPoint ECPoint::operator*(const int& other) const {

}

bool ECPoint::isPointOnECC(const Fp& x, const Fp& y) {
  return (y * y) == (x*x*x + b);
}
