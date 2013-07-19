#include "common.h"

struct Base {
  Base();
  virtual void foo() {}

  int a;
};

struct Child: virtual Base {
  Child();  // Force a vtordisp, see http://llvm.org/PR16406
  virtual void foo();

  int b;
};

#ifdef CONFIG_1
Base::Base() {}
Child::Child() {}

void Child::foo() {
  a = 1;
  b = 2;
}

#else

int main() {
  Child obj;
  obj.a = obj.b = 42;
  obj.foo();

  CHECK_EQ(1, obj.a);
  CHECK_EQ(2, obj.b);
}
#endif
