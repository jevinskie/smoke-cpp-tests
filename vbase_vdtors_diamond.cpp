#include "common.h"

struct A {
  virtual ~A();
};
struct B : virtual A {
  virtual ~B();
};
struct C : virtual A {
  virtual ~C();
};
struct D : B, C {
  virtual ~D();
};

extern int a_calls;
extern int b_calls;
extern int c_calls;
extern int d_calls;

void destroy(D *d);

#ifdef CONFIG_1
int a_calls;
int b_calls;
int c_calls;
int d_calls;
A::~A() { a_calls++; }
B::~B() { b_calls++; }
C::~C() { c_calls++; }
D::~D() { d_calls++; }

void destroy(D *d) {
  delete d;
}
#else

int main() {
  D *d = new D();
  destroy(d);
  CHECK_EQ(1, a_calls);
  CHECK_EQ(1, b_calls);
  CHECK_EQ(1, c_calls);
  CHECK_EQ(1, d_calls);
}
#endif
