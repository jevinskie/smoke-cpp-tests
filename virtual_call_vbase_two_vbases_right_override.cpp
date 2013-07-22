#include "common.h"

struct A {
  virtual void a(void *ptr);
  int a_;
};

struct B {
  virtual void b(void *ptr);
  int b_;
};

struct C : virtual A, virtual B {
  C();  // Force a vtordisp, see http://llvm.org/PR16406
  virtual void b(void *ptr);
  int c_;
};

void foo(C* obj, void *a_ptr);
void bar(C* obj, void *b_ptr);

#ifdef CONFIG_1
C::C() {
}

void foo(C* obj, void *a_ptr) {
  obj->a(a_ptr);
}

void bar(C* obj, void *b_ptr) {
  obj->b(b_ptr);
}

#else
void A::a(void *ptr) {
  CHECK_EQ(ptr, this);
}

void B::b(void *ptr) {
  CHECK(!"Unreached");
}

void C::b(void *ptr) {
  CHECK_EQ(ptr, this);
}

int main() {
  C c;
  foo(&c, (A*)&c);
  bar(&c, (C*)&c);
}
#endif
