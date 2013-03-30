#include "common.h"

struct A {
  int which;
  virtual void Foo();
  virtual void Bar();
};

void testCall(A *a, void (A::*memptr)());

#ifdef CONFIG_1

void testCall(A *a, void (A::*memptr)()) {
  (a->*memptr)();
}

#else

void A::Foo() { which = 1; }
void A::Bar() { which = 2; }

struct B : public A {
  virtual void Foo() { this->which = 3; }
  virtual void Bar() { this->which = 4; }
};

int main() {
  A a;
  a.which = 0;
  testCall(&a, &A::Foo);
  CHECK_EQ(1, a.which);
  a.which = 0;
  testCall(&a, &A::Bar);
  CHECK_EQ(2, a.which);

  B b;
  b.which = 0;
  testCall(&b, &A::Foo);
  CHECK_EQ(3, b.which);
  b.which = 0;
  testCall(&b, &A::Bar);
  CHECK_EQ(4, b.which);
}

#endif
