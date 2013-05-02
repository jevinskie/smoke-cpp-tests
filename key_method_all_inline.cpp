#include "common.h"

struct Foo {
  virtual ~Foo() {}
  virtual int bar() = 0;
};

Foo *GetFoo();

#ifdef CONFIG_1
struct FooImpl : public Foo {
  FooImpl() {}
  virtual ~FooImpl() {}
  virtual int bar() {
    printf("asdf\n");
    return 0xcc;
  }
};

Foo *GetFoo() {
  return new FooImpl();
}
#else
int main() {
  Foo *f = GetFoo();
  CHECK_EQ(f->bar(), 0xcc);
}
#endif
