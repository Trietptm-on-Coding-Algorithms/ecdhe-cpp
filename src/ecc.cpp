#include "ecdhe.h"

mpz_class ECPoint::p;
mpz_class ECPoint::a;
mpz_class ECPoint::b;

void ECPoint::init() {
  p.set_str("fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f", 16);
  a.set_str("0", 10);
  b.set_str("7", 10);
}

ECPoint::ECPoint(mpz_class _x, mpz_class _y) : x(_x), y(_y) {
  if (!isPointOnECC(_x, _y)) {
    std::cerr << "Error: Point (" << _x << ", " << _y << ") is not point on this curve" << std::endl;
    exit(-1);
  }
}

std::ostream& operator<<(std::ostream& _os, const ECPoint& ptr) {
  _os << "(" << ptr.x << ", " << ptr.y << ")";
  return _os;
}

bool ECPoint::operator==(const ECPoint& other) {
  return x == other.x && y == other.y;
}

bool ECPoint::operator!=(const ECPoint& other) {
  return !(*this == other);
}

ECPoint ECPoint::operator+(const ECPoint& other) {
  mpz_class x3(0), y3(0), l(0);
  if(x != other.x) {
    l = (other.y - y) / (other.x - x);
    std::cout << (other.y - y)/(other.x - x) << std::endl;
  } else {
    l = ((3*x*x) + a)/(2*y);
  }
  l %= p;
  std::cout << l << std::endl;

  x3 = ((l*l) - x - other.x) % p;
  y3 = (l*(x - x3 % p)) % p - y % p;
  return ECPoint(x3 % p, y3 % p);
}

bool ECPoint::isPointOnECC(mpz_class x, mpz_class y) {
  return (y * y) % p == (x*x*x + b) % p;
}

class Initializer {
  public:
    Initializer() {
      ECPoint::init();
    }
};
Initializer dummy;
