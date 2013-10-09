#include "common.h"

struct A {
  A();
  ~A();
  virtual void c();
  virtual void d();
  int stage;
};

struct B : virtual A {
  B();
  ~B();
  // B's thunks use static this adjustment, assuming A's layout follows the 
  // members of B.
  virtual void c();
  virtual void d();
  int xxx;
};

// In C, the vbases are laid out in the A, B order. Before we enter C() and
// after we leave ~C(), the static this adjustment in B's thunks should be
// further adjusted account for the different order of A and B.
struct C: virtual B {
  C();
  ~C();
};

#ifdef CONFIG_1
A::A() {
  stage = 1;
  c();
}

B::B() {
  CHECK_EQ(1, stage);
  stage = 2;
  c();
}

// Force ctor and dtor to be compiled in different TUs. 
C::C() {
  CHECK_EQ(2, stage);
  c();
  stage = 3;
}

B::~B() {
  CHECK_EQ(4, stage);
  d();
  stage = 5;
}

A::~A() {
  CHECK_EQ(5, stage);
  d();
}

#else

// Force ctor and dtor to be compiled in different TUs. 
C::~C() {
  CHECK_EQ(3, stage);
  stage = 4;
  d();
}

void A::c() { CHECK_EQ(1, stage); }
void B::c() { CHECK_EQ(2, stage); }

void B::d() { CHECK_EQ(4, stage); }
void A::d() { CHECK_EQ(5, stage); }

int main() {
  C obj;
}
#endif
