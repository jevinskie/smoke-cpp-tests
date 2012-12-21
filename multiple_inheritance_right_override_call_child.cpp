#include "common.h"

class Base1 {
 public:
  virtual void foo() {}

  int a;
};

class Base2 {
 public:
  virtual void bar(void *T, int A, int B, int C) {}

  int b;
};

class Child: public Base1, public Base2 {
 public:
  // This overrides the right child's method,
  // hence requires this adjustment (e.g. thunk)
  virtual void bar(void *T, int A, int B, int C);

  int c;
};

#ifdef CONFIG_1
extern "C" void _exit(int);

void Child::bar(void *T, int A, int B, int C) {
  CHECK_EQ(1, A);
  CHECK_EQ(2, B);
  CHECK_EQ(3, C);
  CHECK_EQ(T, this);
}

#else

int main() {
  Child obj;
  obj.bar(&obj, 1, 2, 3);
}
#endif
