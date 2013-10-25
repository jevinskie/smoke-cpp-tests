// Check that we don't memcpy Foo when passing it by value.
// http://llvm.org/PR5064
#include "common.h"

struct Foo {
  static int dtors;
  Foo *me;
  Foo() { me = this; }

  Foo(const Foo &o) {
    me = this;
  }

  ~Foo() {
    CHECK_EQ(me, this);
    dtors++;
  }
};

void foo(Foo f);

#ifdef CONFIG_1
int Foo::dtors;
void foo(Foo f) {
}

#else
int main() {
  foo(Foo());
  CHECK_EQ(Foo::dtors, 1);
}
#endif
