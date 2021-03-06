#include "common.h"

struct Base1 {
  int a;
};

struct Base2 {
  int b;
};

struct Child: Base1, Base2 {
  int c;
};

struct RetBase {
  virtual Base2 *foo();
};

struct RetChild : RetBase {
  // Child vs Base2 are covariant return types,
  // thus RetChild::foo() overrides RetBase::foo().
  Child *foo();
};

extern Child ret;

#ifdef CONFIG_1
Child ret;

Base2* RetBase::foo() { return 0; }

Child* RetChild::foo() {
  ret.a = 1;
  ret.b = 2;
  ret.c = 3;
  return &ret;
}

#else

void zoo(RetBase* obj) {
  Base2* ret = obj->foo();
  CHECK_NE(0, ret);
  CHECK_EQ(2, ret->b);
}

int main() {
  RetChild obj;
  Child* ret = obj.foo();
  CHECK_NE(0, ret);
  CHECK_EQ(1, ret->a);
  CHECK_EQ(2, ret->b);
  CHECK_EQ(3, ret->c);

  zoo(&obj);
}
#endif
