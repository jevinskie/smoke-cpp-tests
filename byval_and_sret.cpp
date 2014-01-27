#include "common.h"

struct A {
  A() : a(42) {}
  A(const A &o) : a(o.a) {}
  ~A() {}
  int a;
};

A foo(A);
#ifdef CONFIG_1
A foo(A x) {
  CHECK_EQ(42, x.a);
  return x;
}
#else
int main() {
  A x = foo(A());
  CHECK_EQ(42, x.a);
}
#endif
