#include "common.h"

// TODO: need vbase support, but memptr representation in MS ABI is:
// {offset in class, offset in vbtable}

struct A {
  int a;
  void foo();
};

struct B : virtual A {
  int b;
  virtual void bar();
};

struct C : virtual B {
  int c;
};

struct D : C {
  int d;
};

void foo(B *bp, void (B::*memptr)());

#ifdef CONFIG_1

void foo(B *bp, void (B::*memptr)()) {
  (bp->*memptr)();
}

#else

void A::foo() { a = 5; }
void B::bar() { b = 10; }

int main() {
  D c;
#ifdef _MSC_VER
  // http://llvm.org/PR15713
  c.a = c.b = 0;
  foo(&c, &B::foo);
  CHECK_EQ(5, c.a);
#endif
  c.a = c.b = 0;
  foo(&c, &B::bar);
  CHECK_EQ(10, c.b);
}
#endif
