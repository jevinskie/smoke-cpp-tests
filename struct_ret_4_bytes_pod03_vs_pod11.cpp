// http://llvm.org/PR13676
#include "common.h"

struct B {};

// S is a C++11 POD (trivial, standard-layout)
// but not a C++03 POD since it inherits from another class.
struct S : B {
  int a;
};

S foo();

#ifdef CONFIG_1
S foo() {
  S ret;
  ret.a = 1;
  return ret;
}
#else
int main() {
  S s = foo();
  CHECK_EQ(1, s.a);
}
#endif
