#include <memory>
#include "common.h"

struct A {
  A(int a) : a(a) {}
  int a;
};
void foo(std::unique_ptr<A> p);
#ifdef CONFIG_1
void foo(std::unique_ptr<A> p) {
  CHECK_EQ(42, p->a);
}
#else
int main() {
  std::unique_ptr<A> p(new A(42));
  foo(std::move(p));
  CHECK_EQ(nullptr, p.get());
}
#endif
