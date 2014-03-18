#include "common.h"

struct A {
  virtual int foo();
};
struct B : virtual A {
  virtual int bar();
};
struct C : virtual A {
  virtual int foo();
  int c;
};
struct D : B, C {
  virtual int bar();
  int d;
};

#ifdef CONFIG_1
int D::bar() {
  //CHECK_EQ(777, d);
  return C::foo();
}

#else
int C::foo() {
  return c;
}

int B::bar() { CHECK(!"Should not be called"); return 0; }

int A::foo() { CHECK(!"Should not be called"); return 0; }

int main() {
  D d;
  d.d = 777;
  d.c = 42;
  CHECK_EQ(42, d.bar());
}
#endif
