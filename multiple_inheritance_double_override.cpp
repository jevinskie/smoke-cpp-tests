#include "common.h"

class Base1 {
 public:
  virtual void foo(void *T, int x) {}

  int a;
};

class Base2 {
 public:
  virtual void foo(void *T, int x) {}

  int b;
};

class Child: public Base1, public Base2 {
 public:
  // Overrides methods of both bases, thus requires a thunk.
  virtual void foo(void *T, int x);

  int c;
};

#ifdef CONFIG_1
extern "C" void _exit(int);

void Child::foo(void *T, int x) {
  CHECK_EQ(42, x);
  CHECK_EQ(T, this);
}

#else

void call_via_left_base(Base1 *left_base, Child *full_obj) {
  left_base->foo(full_obj, 42);
}

void call_via_right_base(Base2 *right_base, Child *full_obj) {
  right_base->foo(full_obj, 42);
}

int main() {
  Child obj;
  obj.foo(&obj, 42);
  call_via_left_base(&obj, &obj);
  call_via_right_base(&obj, &obj);
}
#endif
