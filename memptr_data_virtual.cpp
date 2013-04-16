#include "common.h"

// TODO: need vbase support, but memptr representation in MS ABI is:
// {offset in class, offset in vbtable}

struct A {
  int a;
};

struct B : virtual A {
  int b;
};

void foo(B *bp, int B::*memptr);

#ifdef CONFIG_1

void foo(B *bp, int B::*memptr) {
  bp->*memptr = 10;
}

#else
int main() {
  B b;
  b.a = b.b = 0;
  foo(&b, &B::b);
  CHECK_EQ(10, b.b);
# ifdef _MSC_VER
  // Taking a pointer to a member of a virtual base is an MSVC extension that
  // didn't make it into the standard: http://llvm.org/PR15713
  b.a = b.b = 0;
  foo(&b, &B::a);
  CHECK_EQ(10, b.a);
# endif
}
#endif
