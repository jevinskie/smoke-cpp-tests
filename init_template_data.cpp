#include "common.h"

struct Foo {
  Foo();
  ~Foo();
  static int ctor_calls;
};

template<typename T>
struct Tmpl {
  T t;
  static Foo f;
};

template<typename T> Foo Tmpl<T>::f;

Foo *getFoo();

#ifdef CONFIG_1
int Foo::ctor_calls = 0;
Foo::Foo() { ctor_calls++; }
Foo::~Foo() {}

Foo *getFoo() {
  return &Tmpl<int>::f;
}
#else
int main() {
  Foo *f1 = &Tmpl<int>::f;
  Foo *f2 = getFoo();
  CHECK_EQ(f1, f2);
  CHECK_EQ(Foo::ctor_calls, 1);
  return 1;
}
#endif
