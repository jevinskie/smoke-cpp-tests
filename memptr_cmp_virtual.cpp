#include "common.h"

struct A { 
  int unused;
};

struct Foo : virtual A {
  int a;
  int b;
  void foo();
  void bar();
  virtual void virtualFoo();
  virtual void virtualBar();
};

bool funcMemptrEq(void (Foo::*l)(), void (Foo::*r)());
bool funcMemptrNeq(void (Foo::*l)(), void (Foo::*r)());

bool dataMemptrEq(int Foo::*l, int Foo::*r);
bool dataMemptrNeq(int Foo::*l, int Foo::*r);

#ifdef CONFIG_1

bool funcMemptrEq(void (Foo::*l)(), void (Foo::*r)()) {
  return l == r;
}

bool funcMemptrNeq(void (Foo::*l)(), void (Foo::*r)()) {
  return l != r;
}

bool dataMemptrEq(int Foo::*l, int Foo::*r) {
  return l == r;
}

bool dataMemptrNeq(int Foo::*l, int Foo::*r) {
  return l != r;
}

#else

void Foo::foo() { printf("foo\n"); }
void Foo::bar() { printf("bar\n"); }
void Foo::virtualFoo() { }
void Foo::virtualBar() { }

void (Foo::*zero_func)();

int main() {
  CHECK(funcMemptrEq(&Foo::foo, &Foo::foo));
  CHECK(funcMemptrEq(&Foo::virtualFoo, &Foo::virtualFoo));
  CHECK(!funcMemptrEq(&Foo::foo, &Foo::bar));
  CHECK(!funcMemptrEq(&Foo::foo, &Foo::virtualFoo));
  CHECK(!funcMemptrEq(&Foo::bar, &Foo::foo));
  CHECK(funcMemptrEq(&Foo::bar, &Foo::bar));
  CHECK(!funcMemptrEq(&Foo::foo, zero_func));

  CHECK(!funcMemptrNeq(&Foo::foo, &Foo::foo));
  CHECK(funcMemptrNeq(&Foo::foo, &Foo::bar));
  CHECK(funcMemptrNeq(&Foo::bar, &Foo::foo));
  CHECK(funcMemptrNeq(&Foo::bar, &Foo::virtualFoo));
  CHECK(!funcMemptrNeq(&Foo::bar, &Foo::bar));
  CHECK(funcMemptrNeq(&Foo::foo, zero_func));
  CHECK(funcMemptrNeq(&Foo::bar, zero_func));

  CHECK(dataMemptrEq(&Foo::a, &Foo::a));
  CHECK(!dataMemptrEq(&Foo::a, &Foo::b));
  CHECK(!dataMemptrEq(&Foo::a, 0));
  CHECK(!dataMemptrEq(&Foo::b, 0));
  CHECK(dataMemptrNeq(&Foo::b, 0));
}

#endif
