#include "common.h"

struct A {
  int which;
  void Foo();
  void Bar();
};

void testCall(A *a, void (A::*memptr)());

#ifdef CONFIG_1

void testCall(A *a, void (A::*memptr)()) {
  (a->*memptr)();
}

#else

void A::Foo() { which = 1; }
void A::Bar() { which = 2; }

int main() {
  A a;
  a.which = 0;
  testCall(&a, &A::Foo);
  CHECK_EQ(1, a.which);
  testCall(&a, &A::Bar);
  CHECK_EQ(2, a.which);
  a.which = 0;
}
#endif
