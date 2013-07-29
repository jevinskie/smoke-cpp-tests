#include "common.h"

class Base1 {
 public:
  virtual void foo() {}

  int a;
};

class Base2 {
 public:
  virtual void bar(void *T, int x) {}

  int b;
};

class Middle: public Base1, public Base2 {
};

class Child: public Middle {
 public:
  // This overrides the right child's method,
  // hence requires this adjustment (e.g. thunk)
  virtual void bar(void *T, int x);

  int c;
};

#ifdef CONFIG_1
void Child::bar(void *T, int x) {
  CHECK_EQ(42, x);
  CHECK_EQ(T, this);
}

#else

void call_via_base(Base2 *right_base, Child *full_obj) {
  right_base->bar(full_obj, 42);
}

int main() {
  Child obj;
  call_via_base(&obj, &obj);
  obj.bar(&obj, 42);
}
#endif
