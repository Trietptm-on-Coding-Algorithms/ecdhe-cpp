#include <fstream>
#include "ecdhe.h"
#include "ecpoint.h"
#include "fp.h"

int main(int, char**) {
  Fp::init("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
  ECPoint::init();
  ECPoint G;
  std::cout << "Start Fp p; p *= p(1000*1000 Times repeat)" << std::endl;
  Fp p = mpz_class(time(0));
  clock_t start = clock();
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      p *= p;
    }
  }
  clock_t end = clock();
  std::cout << "Finished Fp." << std::endl << "Time: " << ((double)end - start)/CLOCKS_PER_SEC << "sec" << std::endl;

  std::cout << "Start G = 10000G(1000 Times repeat)" << std::endl;
  G = ECPoint(mpz_class(ES_ECC_X), mpz_class(ES_ECC_Y));
  start = clock();
  for (int i = 0; i < 1000; i++) {
    G = 10000*G;
  }
  end = clock();
  std::cout << "Finished ECPoint." << std::endl << "Time: " << ((double)end - start)/CLOCKS_PER_SEC << "sec" << std::endl;

  std::cout << "Start G = 2G(1000*1000 Times repeat)" << std::endl;
  G = ECPoint(mpz_class(ES_ECC_X), mpz_class(ES_ECC_Y));
  start = clock();
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      G = G+G;
    }
  }
  end = clock();
  std::cout << "Finished ECPoint." << std::endl << "Time: " << ((double)end - start)/CLOCKS_PER_SEC << "sec" << std::endl;
/*
  mpz_class a = get_random_bytes(1024);
  std::cout << "a = " << a << std::endl;

  mpz_class b = get_random_bytes(1024);
  std::cout << "b = " << b << std::endl;

  ECPoint kA = a*G;
  std::cout << "kA = " << kA << std::endl;

  ECPoint kB = b*G;
  std::cout << "kB = " << kB << std::endl;

  ECPoint secret_A = kA * b;
  std::cout << "secret_A = " << secret_A << std::endl;

  ECPoint secret_B = kB * a;
  std::cout << "secret_B = " << secret_B << std::endl;

  std::cout << "secret_A == secret_B -> ";
  if (secret_A == secret_B) {
    std::cout << "true";
  } else {
    std::cout << "false";
  }
  std::cout << std::endl;
  */
}
