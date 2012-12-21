#include "common.h"

class Base1 {
 public:
  virtual void foo() {}

  int a;
};

class Base2 {
 public:
  virtual void bar() {}

  int b;
};

class Child: public Base1, public Base2 {
 public:
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
