#include "common.h"

struct A {
  virtual void foo() {}
  int a;
};

struct B {
  virtual ~B() {}
  int b;
};

struct C {
  virtual ~C() {}
  int c;
};

struct D : A, B, virtual C {
  virtual ~D();
  int d;
};

extern int d_dtor_calls;

#ifdef CONFIG_1
D::~D() {
  CHECK_EQ(1, a);
  CHECK_EQ(2, b);
  CHECK_EQ(3, c);
  CHECK_EQ(4, d);
  d_dtor_calls++;
}

#else

int d_dtor_calls = 0;

int main() {
  D *obj = new D;
  obj->a = 1;
  obj->b = 2;
  obj->c = 3;
  obj->d = 4;
  delete obj;
  CHECK_EQ(1, d_dtor_calls);
}
#endif
