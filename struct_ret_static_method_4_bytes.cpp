// http://llvm.org/PR13676
#include "common.h"

struct S {
  int a;
};

class C {
 public:
  static S foo();
};

#ifdef CONFIG_1
S C::foo() {
  S ret;
  ret.a = 1;
  return ret;
}
#else
int main() {
  C c;
  S s = c.foo();
  CHECK_EQ(1, s.a);
}
#endif
