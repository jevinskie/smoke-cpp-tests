#include "common.h"

struct A {
  A(int a) : a(a) {}
  A(const A &o) : a(o.a) {}
  ~A();
  int a;

  static A foo(A);
};

struct B {
  B(const A &o) : b(o.a) {}
  int b;
};

#ifdef CONFIG_1
static int returns_zero() { return 0; }

A::~A() {
  // Zero out the return register.
  returns_zero();
}

A A::foo(A a) {
  // ~A will clobber eax for us, to make this more robust.
  A requires_cleanup(1);
  return a;
}

#else
int main() {
  // MSVC will call B's implicit A constructor and it will use eax to do it.
  B b = A::foo(A(42));
  CHECK_EQ(42, b.b);
}
#endif
