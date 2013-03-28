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
  b.a = b.b = 0;
  foo(&b, &B::a);
  CHECK_EQ(10, b.a);
}
#endif
