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
  if (!isPointOnECC(_x, _y)) {
    std::cerr << "Error: Point (" << _x << ", " << _y << ") is not point on this curve" << std::endl;
    throw std::runtime_error("Point is not point on this curve.");
  }
  x = _x;
  y = _y;
}

std::ostream& operator<<(std::ostream& _os, const ECPoint& ptr) {
  _os << "(" << ptr.x << ", " << ptr.y << ")";
  return _os;
}

bool operator==(const ECPoint& me, const ECPoint& other) {
  return (me.x == other.x && me.y == other.y);
}

bool operator!=(const ECPoint& me, const ECPoint& other) {
  return !(me == other);
}

ECPoint operator+(const ECPoint& me, const ECPoint& other) {
  Fp x3(0), y3(0), l(0);

  if (me.x != other.x) {
    l = (other.y - me.y) / (other.x - me.x);
  } else {
    l = (Fp(3)*me.x*me.x) / (Fp(2)*me.y);
  }

  x3 = (l*l - (me.x + other.x));
  y3 = (l*me.x - l*x3 - me.y);
  std::cout << x3 << y3 << std::endl;
  return ECPoint(x3, y3);
}

ECPoint operator*(const ECPoint& me, int n) {
  if (n == 1) {
    return me;
  } else if (n == 2) {
    std::cout << me << std::endl;
    return me + me;
  }
  ECPoint P(me);
  ECPoint ret;
  while(n != 0) {
    if (n % 2 == 1) {
      ret = P + ret;
    }
    P = P*2;
    n /= 2;
    //std::cout << ret << " : " << P << " : " << n << std::endl;
  }
  std::cout << ret << " : " << P << " : " << n << std::endl;
  return ret;
}

bool ECPoint::isPointOnECC(const Fp& x, const Fp& y) {
  return (y * y) == (x*x*x + b);
}
