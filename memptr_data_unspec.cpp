#include "common.h"

struct A;
struct B;

void foo(A *o, int A::*memptr);
void bar(B *o, int B::*memptr);

// Locks in the size model.
static int A::*a_memptr;
static int B::*b_memptr;

#ifdef CONFIG_1

void foo(A *o, int A::*memptr) {
  //if (memptr)
    o->*memptr = 10;
}

void bar(B *o, int B::*memptr) {
  //if (memptr)
    o->*memptr = 10;
}

#else

struct A {
  int a;
  int aa;
};

struct B : virtual A {
  int b;
};

struct C : B {
  int c;
};

int main() {
  // Unspecified memptrs that ultimately didn't need vbase adjustment.
  A a;
  a.a = a.aa = 0;
  foo(&a, &A::a);
  CHECK_EQ(10, a.a);
  a.a = a.aa = 0;
  foo(&a, &A::aa);
  CHECK_EQ(10, a.aa);
  a.a = a.aa = 0;
  //foo(&a, 0);
  //CHECK_EQ(0, a.a);
  //CHECK_EQ(0, a.aa);

  // Unspecified memptrs that need virtual base adjustments.
  C c;
  c.a = c.b = c.c = 0;
  bar(&c, &C::b);
  CHECK_EQ(10, c.b);
# ifdef _MSC_VER
  // Taking a pointer to a member of a virtual base is an MSVC extension that
  // didn't make it into the standard: http://llvm.org/PR15713
  c.a = c.b = c.c = 0;
  bar(&c, &C::a);
  CHECK_EQ(10, c.a);
# endif
}
#endif
