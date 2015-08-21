#pragma once

#include "ecdhe.h"
#include "ecpoint.h"
#include "fp.h"
#include <stdexcept>

#define ES_ASSERT_EQ(x,y) ES_ASSERTION(x == y)

#define ES_ASSERT_NEQ(x,y) ES_ASSERTION(x != y)

#define ES_ASSERTION(cond) do {\
  st_test++;\
  std::cout << "[+] Testing " << #cond << "...";\
  try { \
    if(!(cond)) { \
      std::cout << "\033[31mFAILED\033[0m" << std::endl; \
      std::cerr << "[-] \033[31mAssertion Failed: <" << __FILE__ << "> " << __FUNCTION__ << ":" << __LINE__ << " -> !(" << #cond << "\033[0m" << std::endl;\
      st_err++; \
    } else { \
      std::cout << "\033[32mOK\033[0m" << std::endl; \
    }\
  } catch (const std::runtime_error& e) { \
      std::cout << "\033[31mFAILED(EXCEPTION)\033[0m" << std::endl; \
      std::cerr << "[-] \033[31mAssertion Failed: <" \
          << __FILE__ << "> " << __FUNCTION__ << ":" << __LINE__ \
          << "(Exception occurerd!) -> !(" << #cond << ")\033[0m" \
          << "\n\t-> \033[01;04;31m" << e.what() << "\033[0m" << std::endl;\
      st_err++; \
  } \
} while(0)

void exec_test();
