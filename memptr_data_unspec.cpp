#include "common.h"

struct B;

void foo(B *bp, int B::*memptr);

// Locks in the size model.
static int B::*g_memptr;

#ifdef CONFIG_1

void foo(B *bp, int B::*memptr) {
  bp->*memptr = 10;
}

#else

struct A {
  int a;
};

struct B : virtual A {
  int b;
};

struct C : B {
  int c;
};

int main() {
  C c;
  c.a = c.b = c.c = 0;
  foo(&c, &C::b);
  CHECK_EQ(10, c.b);
# ifdef _MSC_VER
  // Taking a pointer to a member of a virtual base is an MSVC extension that
  // didn't make it into the standard: http://llvm.org/PR15713
  c.a = c.b = c.c = 0;
  foo(&c, &C::a);
  CHECK_EQ(10, c.a);
# endif
}
#endif
