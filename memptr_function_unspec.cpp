#include "common.h"

struct A;
struct B;

void foo(A *o, void (A::*memptr)());
void bar(B *o, void (B::*memptr)());

// Locks in the size model.
static int A::*a_memptr;
static int B::*b_memptr;

#ifdef CONFIG_1

void foo(A *o, void (A::*memptr)()) {
  (o->*memptr)();
}

void bar(B *o, void (B::*memptr)()) {
  (o->*memptr)();
}

#else

struct A {
  int a;
  void foo() { a = 10; }
  void bar() { a = 20; }
};

struct Spacer {
  int pad;
};

struct B : Spacer, A {
  int b;
  //virtual void bar() { b = 30; }
};

struct C : B {
  int c;
  //virtual void bar() { c = 40; }
};

int main() {
  // Unspecified memptrs that ultimately didn't need vbase adjustment.
  A a;
  a.a = 0;
  foo(&a, &A::foo);
  CHECK_EQ(10, a.a);
  a.a = 0;
  foo(&a, &A::bar);
  CHECK_EQ(20, a.a);
  a.a = 0;

#if 1
# ifdef _MSC_VER
  // Unspecified memptrs that need virtual base adjustments.
  C c;
  c.a = c.b = c.c = 0;
  bar(&c, &A::foo);
  CHECK_EQ(10, c.a);
  // Taking a pointer to a member of a virtual base is an MSVC extension that
  // didn't make it into the standard: http://llvm.org/PR15713
  c.a = c.b = c.c = 0;
  bar(&c, &A::bar);
  CHECK_EQ(20, c.a);
# endif
#endif
}
#endif
