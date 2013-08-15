#include "common.h"

struct Foo {
  Foo();
  ~Foo();
  int x;
  static int ctor_calls;
};

inline __forceinline void getFoos(Foo **a, Foo **b) {
  static Foo FooA;
  static Foo FooB;
  *a = &FooA;
  *b = &FooB;
}

void callGetFoosInOtherTU();

#ifdef CONFIG_1
int Foo::ctor_calls;

Foo::Foo() : x(++ctor_calls) { }

Foo::~Foo() {
  exit(0);
}

void callGetFoosInOtherTU() {
  Foo *a, *b;
  getFoos(&a, &b);
  CHECK_EQ(1, a->x);
  CHECK_EQ(2, b->x);
}

#else
int main() {
  Foo *a, *b;
  getFoos(&a, &b);
  CHECK_EQ(1, a->x);
  CHECK_EQ(2, b->x);
  callGetFoosInOtherTU();
  return 1;
}
#endif
