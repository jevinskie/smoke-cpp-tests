#include "common.h"

struct A {
  A() : a(1) { }
  int a;
  virtual int foo();
};
struct B {
  B() : b(2) { }
  int b;
  virtual int foo();
};
struct C : A, B {
  C() : c(3) { }
  int c;
  virtual int foo();
};

#ifdef CONFIG_1

int A::foo() { return a; }
int B::foo() { return b; }
int C::foo() { return c; }

#else

int main() {
  A a;
  CHECK_EQ(1, a.foo());
  B b;
  CHECK_EQ(2, b.foo());
  C c;
  CHECK_EQ(3, c.foo());
}
#endif
