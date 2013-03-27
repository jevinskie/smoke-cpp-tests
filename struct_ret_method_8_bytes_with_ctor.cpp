// http://llvm.org/PR13676
#include "common.h"

struct S {
  int a, b;
  S(char *) {}
};

class C {
 public:
  S foo();
};

#ifdef CONFIG_1
S C::foo() {
  S ret(0);
  ret.a = 1;
  ret.b = 2;
  return ret;
}
#else
int main() {
  C c;
  S s = c.foo();
  CHECK_EQ(1, s.a);
  CHECK_EQ(2, s.b);
}
#endif
