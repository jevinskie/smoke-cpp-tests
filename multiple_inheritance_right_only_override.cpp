#include "common.h"

struct Base1 {
  int a;
};

struct Base2 {
  virtual void foo() {}

  int b;
};

// Only Base2 has its own vfptr.
struct Child: Base1, Base2 {
  virtual void foo();

  int c;
};

#ifdef CONFIG_1
void Child::foo() {
  a = 1;
  b = 2;
  c = 3;
}

#else

int main() {
  Child obj;
  obj.a = obj.b = obj.c = 42;
  obj.foo();

  CHECK_EQ(1, obj.a);
  CHECK_EQ(2, obj.b);
  CHECK_EQ(3, obj.c);
}
#endif
