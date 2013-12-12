#include "common.h"

// http://llvm.org/PR18233

struct A {
  A(int a) : a(a) {}
  int a;
};
struct B : virtual A {
  B(A &o);
};

#ifdef CONFIG_1
// Used to crash dereferencing o here.
B::B(A &o) : A(o.a) {}

#else
int main() {
  A a(42);
  B copy(a);
  CHECK_EQ(copy.a, 42);
}
#endif
