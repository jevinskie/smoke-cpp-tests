#include "common.h"

struct A {
  A();
  virtual int f();
  int a;
};

struct B : virtual A {
  B();
  int b;
};

struct C : B {
  C();
  virtual int f();
  int c;
};

struct D : C {
  D();
  int d;
};

#ifdef CONFIG_1
int C::f() { return c; }

#else
A::A() : a(1) { }
int A::f() { return a; }

B::B() : b(2) { }
C::C() : c(3) { }
D::D() : d(4) { }

int main() {
  D obj;
  CHECK_EQ(3, obj.f());
}
#endif
