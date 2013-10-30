#include "common.h"

struct X {
  virtual void x() {}
};

struct A {
  A();
  ~A();
  virtual void c(void*);
  virtual void d(void*);
  int stage_a;
};

struct Y : X, A {};

struct B : virtual Y {
  B();
  ~B();
  // B's thunks use static this adjustment, assuming A's layout follows the 
  // members of B.
  virtual void c(void*);
  virtual void d(void*);
  int stage_b;
};

// In C, the vbases are laid out in the A, B order. Before we enter C() and
// after we leave ~C(), the static this adjustment in B's thunks should be
// further adjusted account for the different order of A and B.
struct C : virtual B {
  C();
  ~C();
  void call_c();
};

struct Z { int z; };

struct D : virtual Y, virtual Z, C {
};

#ifdef CONFIG_1
A::A() {
  stage_a = 1;
  c(this);
}

B::B() {
  CHECK_EQ(1, stage_a);
  stage_a = 2;
  stage_b = 1;
  c(this);
}

// Force ctor and dtor to be compiled in different TUs. 
C::C() {
  CHECK_EQ(2, stage_a);
  CHECK_EQ(1, stage_b);
  call_c();
  stage_a = 3;
  stage_b = 2;
}

void C::call_c() {
  c((B*)this);
}

B::~B() {
  CHECK_EQ(4, stage_a);
  CHECK_EQ(3, stage_b);
  d(this);
  stage_a = 5;
}

A::~A() {
  CHECK_EQ(5, stage_a);
  d(this);
}

#else

// Force ctor and dtor to be compiled in different TUs. 
C::~C() {
  CHECK_EQ(3, stage_a);
  CHECK_EQ(2, stage_b);
  stage_a = 4;
  stage_b = 3;
  d((B*)this);
}

void A::c(void *p) {
  CHECK_EQ(this, p);
  CHECK_EQ(1, stage_a);
}

void B::c(void *p) {
  CHECK_EQ(this, p);
  CHECK_EQ(2, stage_a);
  CHECK_EQ(1, stage_b);
}


void B::d(void *p) {
  CHECK_EQ(this, p);
  CHECK_EQ(4, stage_a);
  CHECK_EQ(3, stage_b);
}

void A::d(void *p) {
  CHECK_EQ(this, p);
  CHECK_EQ(5, stage_a);
}

int main() {
  D obj;
}
#endif
