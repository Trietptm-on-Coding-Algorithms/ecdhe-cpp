#pragma once

#include <ecdhe.h>

#define ES_ASSERT_EQ(x,y) do {\
  st_test++;\
  std::cout << "[+] Testing " << #x << " == " << #y << "...";\
  if((x) != (y)) { \
    std::cout << "\033[31mFAILED\033[0m" << std::endl; \
    std::cerr << "[-] \033[31mAssertion Failed: <" << __FILE__ << "> " << __FUNCTION__ << ":" << __LINE__ << " -> " << #x << " != " << #y << "\033[0m" << std::endl;\
    st_err++; \
  } else { \
    std::cout << "\033[32mOK\033[0m" << std::endl; \
  }\
} while(0)

#define ES_ASSERT_NEQ(x,y) do {\
  st_test++;\
  std::cout << "[+] Testing " << #x << " != " << #y << "...";\
  if((x) != (y)) { \
    std::cout << "\033[31mFAILED\033[0m" << std::endl; \
    std::cerr << "[-] \033[31mAssertion Failed: <" << __FILE__ << "> " << __FUNCTION__ << ":" << __LINE__ << " -> " << #x << " == " << #y << "\033[0m" << std::endl;\
    st_err++; \
  } else { \
    std::cout << "\033[32mOK\033[0m" << std::endl; \
  }\
} while(0)

void exec_test();
