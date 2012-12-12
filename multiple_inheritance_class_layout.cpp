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
  void fill();

  int c;
};

#ifdef CONFIG_1
void Child::fill() {
  a = 1;
  b = 2;
  c = 3;
}

#else
int main() {
  Child obj;
  obj.a = obj.b = obj.c = 42;
  obj.fill();

  CHECK(obj.a == 1);
  CHECK(obj.b == 2);
  CHECK(obj.c == 3);
}
#endif
