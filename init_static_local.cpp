#include "common.h"

struct Foo {
  Foo();
  ~Foo();
  int x;
};

void getFoos(Foo **a, Foo **b);

#ifdef CONFIG_1
Foo::Foo() : x(1) { }

Foo::~Foo() {
  exit(0);
}

void getFoos(Foo **a, Foo **b) {
  static Foo FooA;
  static Foo FooB;
  *a = &FooA;
  *b = &FooB;
}

#else
int main() {
  Foo *a, *b;
  getFoos(&a, &b);
  CHECK_EQ(1, a->x);
  CHECK_EQ(1, b->x);
  getFoos(&a, &b);
  CHECK_EQ(1, a->x);
  CHECK_EQ(1, b->x);
  return 1;
}
#endif
