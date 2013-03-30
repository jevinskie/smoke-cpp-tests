#include "common.h"

// Derived from clang's CodeGenCXX/member-function-pointers.cpp test.

struct A {
  int nonEmpty;
  void foo();
};
struct B : public A {
  virtual void requireNonZeroAdjustment();
};

void testCall(B *bp, void (B::*memptr)());

#ifdef CONFIG_1

void testCall(B *bp, void (B::*memptr)()) {
  (bp->*memptr)();
}

#else

void B::requireNonZeroAdjustment() { }

static int which;

void A::foo() { nonEmpty = 1; }

int main() {
  B obj;
  obj.nonEmpty = 0;
  testCall(&obj, &A::foo);
  CHECK_EQ(1, obj.nonEmpty);
}

#endif
