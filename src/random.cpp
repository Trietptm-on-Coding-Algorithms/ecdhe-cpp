#include "ecdhe.h"
#include <fstream>

int read_urandom() {
  char buf[4];
  std::ifstream ifs("/dev/urandom");
  if (ifs.fail()) {
    std::cerr << "Error occurerd : unable to read /dev/urandom." << std::endl;
    exit(-1);
  }
  ifs.read(buf, 4);
  return ((int*)buf)[0];
}

mpz_class get_random_bytes(const int bit) {
  mpz_class rnd;
  for(int i = 0; i < bit; i++) {
    rnd |= read_urandom() % 4 > 2;
    rnd <<= 1;
  }
  if (rnd < 0) {
    rnd = -rnd;
  }
  if (rnd == 0) {
    return get_random_bytes(bit);
  }
  return rnd;
}
