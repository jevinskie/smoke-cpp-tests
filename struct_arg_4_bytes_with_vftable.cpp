// http://llvm.org/PR13676
#include "common.h"

struct S {
  int a;
  virtual void foo() {}
};

void foo(S s);

#ifdef CONFIG_1
void foo(S s) {
  CHECK_EQ(1, s.a);
}
#else
int main() {
  S s;
  s.a = 1;
  foo(s);
}
#endif
