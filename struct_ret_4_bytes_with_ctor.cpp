// http://llvm.org/PR13676
#include "common.h"

struct S {
  S(int x, int y) {}
  int a;
};

S foo();

#ifdef CONFIG_1
S foo() {
  S ret(3, 4);
  ret.a = 1;
  return ret;
}
#else
int main() {
  S s = foo();
  CHECK_EQ(1, s.a);
}
#endif
