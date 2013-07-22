#include "common.h"

struct A {
  virtual void a(void *ptr);
  int a_;
};

struct B {
  virtual void b(void *ptr);
  int b_;
};

struct C : A, B {
  int c_;
};

struct D: virtual C {
  D() {}  // Force a vtordisp, see http://llvm.org/PR16406
  virtual void a(void *ptr);
  virtual void b(void *ptr);
  int d_;
};

void foo(D* obj, void *a_ptr);
void bar(D* obj, void *b_ptr);

#ifdef CONFIG_1
void foo(D* obj, void *a_ptr) {
  obj->a(a_ptr);
}

void bar(D* obj, void *b_ptr) {
  obj->b(b_ptr);
}

void zoo(B* obj) {
  obj->b(0);
}

#else

void A::a(void *ptr) {
  CHECK(!"Ooops");
}

void B::b(void *ptr) {
  CHECK(!"Ooops");
}

void D::a(void *ptr) {
  CHECK_EQ(ptr, this);
}

void D::b(void *ptr) {
  CHECK_EQ(ptr, this);
}

int main() {
  D d;
  foo(&d, &d);
  bar(&d, &d);
}
#endif
