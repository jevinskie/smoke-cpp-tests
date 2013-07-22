#include "common.h"

struct A {
  virtual void foo(void *ptr);
  int a_;
};

struct B {
  virtual void foo(void *ptr);
  int b_;
};

struct C : virtual A, virtual B {
  virtual ~C() {}  // Force a vtordisp, see http://llvm.org/PR16406
  virtual void foo(void *ptr);
  int c_;
};

void foo(C* obj, void *a_ptr);

#ifdef CONFIG_1
void foo(C* obj, void *a_ptr) {
  obj->foo(a_ptr);
}

#else

void A::foo(void *ptr) {
  CHECK(!"Unreached");
}

void B::foo(void *ptr) {
  CHECK(!"Unreached");
}

void C::foo(void *ptr) {
  CHECK_EQ(ptr, this);
  c_++;
}

int main() {
  C c;
  foo(&c, (C*)&c);
}
#endif
