#include "common.h"

// TODO: need vbase support, but memptr representation in MS ABI is:
// {offset in class, offset in vbtable}

struct A {
  int a;
};

struct B : virtual A {
  int b;
};

struct C : virtual B {
  int c;
};

struct D : C {
  int d;
};

void foo(C *bp, int B::*memptr);

#ifdef CONFIG_1

void foo(C *bp, int B::*memptr) {
  bp->*memptr = 10;
}

#else
int main() {
  D o;
#ifdef _MSC_VER
  // Taking a pointer to a member of a virtual base is an MSVC extension that
  // didn't make it into the standard: http://llvm.org/PR15713
  o.a = o.b = o.c = o.d = 0;
  foo(&o, &A::a);
  CHECK_EQ(10, o.a);
#endif
  o.a = o.b = o.c = o.d = 0;
  foo(&o, &B::b);
  CHECK_EQ(10, o.b);
  //o.a = o.b = o.c = o.d = 0;
  //foo(&o, &C::c);
  //CHECK_EQ(10, o.c);
  //o.a = o.b = o.c = o.d = 0;
  //foo(&o, &D::d);
  //CHECK_EQ(10, o.d);
}
#endif
