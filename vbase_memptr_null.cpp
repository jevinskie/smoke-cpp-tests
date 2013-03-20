#include "common.h"

// Same vbase diamond as vbase_memptr, but this time we're just making a null
// memptr, passing it between TUs, and testing for null on the other side.

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

bool foo(int B::*memptr);

#ifdef CONFIG_1

bool foo(int B::*memptr) {
  // Don't do return memptr, since it's not convertible to bool directly.
  if (memptr)
    return true;
  return false;
}

#else
int main() {
  int B::*memptr = 0;
  bool res = foo(memptr);
  CHECK_EQ(false, res);
  memptr = &B::b;
  res = foo(memptr);
  CHECK_EQ(true, res);
}
#endif
