// http://llvm.org/PR13676
#include "common.h"

struct S {
  S(int a, int b) : a(a), b(b) {}
  S(const struct S &s) { a = s.a; b = s.b; }
  int a, b;
};

S foo();

#ifdef CONFIG_1
S foo() {
  S ret(3, 4);
  ret.a = 1;
  ret.b = 2;
  return ret;
}
#else
int main() {
  S s = foo();
  CHECK_EQ(1, s.a);
  CHECK_EQ(2, s.b);
}
#endif
