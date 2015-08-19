#include "ecdhe.h"

const mpz_class secp256k1_p("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
const mpz_class secp256k1_a("0");
const mpz_class secp256k1_b("7");

ECPoint::ECPoint(mpz_class _x, mpz_class _y)
  : x(_x), y(_y) {
  if (!isPointOnECC(_x, _y)) {
    std::cerr << "Error: Point (" << _x << ", " << _y << ") is not point on secp256k1" << std::endl;
    exit(-1);
  }
}
