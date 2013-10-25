#include "common.h"

struct Foo {
  virtual int foo() { return 1; }
};

int bar(Foo *f, int (Foo::*mp)());

#ifdef CONFIG_1
int bar(Foo *f, int (Foo::*mp)()) {
  return (f->*mp)();
}

#else
struct Bar : Foo {
  virtual int foo() { return 2; }
};
int main() {
  Foo a;
  int x = bar(&a, &Foo::foo);
  CHECK_EQ(x, 1);
  Bar b;
  x = bar(&b, &Foo::foo);
  CHECK_EQ(x, 2);
}
#endif
