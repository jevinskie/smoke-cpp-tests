#include "common.h"

// http://llvm.org/PR17382

extern int state;

struct C {
  virtual void f(int);
  virtual void g();
  virtual void f(double);
};

void foo(C* obj);

#ifdef CONFIG_1
int state;

void foo(C* obj) {
  obj->f(42);
  obj->g();
  obj->f(42.13);
}
#else
void C::f(int x) {
  CHECK_EQ(0, state);
  CHECK_EQ(42, x);
  state++;
}

void C::g() {
  CHECK_EQ(1, state);
  state++;
}

void C::f(double d) {
  CHECK_EQ(2, state);
  CHECK_EQ(42.13, d);
  state++;
}

int main() {
  C c;
  foo(&c);
  CHECK_EQ(3, state);
}
#endif
