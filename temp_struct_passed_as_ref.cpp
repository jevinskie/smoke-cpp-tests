#include "common.h"

// This has been failing in Clang, see http://llvm.org/PR13761

struct S {
  S();
  int a, b;
};

#ifdef CONFIG_1
  S::S() : a(1), b(2) {}
#else
  void foo(const struct S &s) {
    CHECK_EQ(1, s.a);
    CHECK_EQ(2, s.b);
  }

  int main() {
    foo(S());
  }
#endif
