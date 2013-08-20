#define _HAS_EXCEPTIONS 0

#if CONFIG_1

#include <sstream>
void foo() {
  std::stringstream ss;
}

#else

#include <iostream>
int main() {
  std::cout << "cout vs sstream\n";
}

#endif
