#include "common.h"

struct A {
  A() : a(42) {}
  A(const A &o) : a(o.a) {}
  ~A() {}
  int a;
  A foo(A o);
};

#ifdef CONFIG_1
A A::foo(A x) {
  A y(*this);
  CHECK_EQ(42, x.a);
  CHECK_EQ(42, y.a);
  y.a += x.a;
  CHECK_EQ(84, y.a);
  return y;
}
#else
int main() {
  A x;
  A y = x.foo(x);
  CHECK_EQ(84, y.a);
}
#endif
