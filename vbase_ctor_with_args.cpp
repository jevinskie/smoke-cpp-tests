#include "common.h"

// http://llvm.org/PR18233

struct A { };

struct B : virtual A {
  B(int arg);
};

#ifdef CONFIG_1
B::B(int arg) {
  CHECK_EQ(42, arg);
}

#else
int main() {
  B obj(42);
}
#endif
