#include "common.h"

struct A {
  A(int a) : a(a) {}
  A(const A &o) : a(o.a) {}
  ~A() {}
  int a;
};

struct B {
  int b;
};

int foo(A a, B b);

#ifdef CONFIG_1
int foo(A a, B b) {
  CHECK_EQ(42, a.a);
  CHECK_EQ(13, b.b);
  return a.a + b.b;
}
#else
int main() {
  B b;
  b.b = 13;
  int c = foo(A(42), b);
  CHECK_EQ(55, c);
}
#endif
