#include "common.h"

struct A {
  virtual ~A() {}
  int a;
};

struct B {
  virtual ~B() {}
  int b;
};

struct C : virtual A, B {
  virtual ~C();
  int c;
};

extern int c_dtor_calls;

#ifdef CONFIG_1
C::~C() {
  CHECK_EQ(1, a);
  CHECK_EQ(2, b);
  CHECK_EQ(3, c);
  c_dtor_calls++;
}

#else

int c_dtor_calls = 0;

int main() {
  C *obj = new C;
  obj->a = 1;
  obj->b = 2;
  obj->c = 3;
  delete obj;
}
#endif
