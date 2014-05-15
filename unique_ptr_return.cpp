#include <memory>
#include "common.h"

struct A {
  A(int a) : a(a) {}
  int a;
};
std::unique_ptr<A> foo();
#ifdef CONFIG_1
std::unique_ptr<A> foo() {
  return std::make_unique<A, int>(42);
}
#else
int main() {
  std::unique_ptr<A> p(foo());
  CHECK_EQ(42, p->a);
}
#endif
