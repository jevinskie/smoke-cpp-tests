// http://llvm.org/PR13676
#include "common.h"

struct S {
  int a, b, c;
};

class C {
 public:
  static S foo();
};

#ifdef CONFIG_1
S C::foo() {
  S ret;
  ret.a = 1;
  ret.b = 2;
  ret.c = 3;
  return ret;
}
#else
int main() {
  C c;
  S s = c.foo();
  CHECK_EQ(1, s.a);
  CHECK_EQ(2, s.b);
  CHECK_EQ(3, s.c);
}
#endif
