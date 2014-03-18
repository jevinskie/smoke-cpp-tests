#include "common.h"

struct A {
  virtual ~A() {}
  int a;
};

struct B : virtual A {
  virtual ~B() {}
  int b;
};

struct C : virtual A {
  virtual ~C() {}
  void destroy();
  int c;
};

struct D : B, C {
  virtual ~D() {}
  int d;
};

struct E {
  virtual ~E() {}
  int e;
};

struct F : D, E {
  virtual ~F();
  int f;
};

extern int d_dtor_calls;

#ifdef CONFIG_1
F::~F() {
  CHECK_EQ(1, a);
  CHECK_EQ(2, b);
  CHECK_EQ(3, c);
  CHECK_EQ(4, d);
  CHECK_EQ(5, e);
  CHECK_EQ(6, f);
  d_dtor_calls++;
}

#else

int d_dtor_calls = 0;

void C::destroy() {
  delete this;
}

int main() {
  F *obj = new F;
  obj->a = 1;
  obj->b = 2;
  obj->c = 3;
  obj->d = 4;
  obj->e = 5;
  obj->f = 6;
  obj->destroy();
  CHECK_EQ(1, d_dtor_calls);
}
#endif
