#include "common.h"

struct A {
  A(int a) : a(a) {}
  A(const A &o) : a(o.a) {}
  ~A() {}
  int a;
};

void foo(int a, A b, float c, A d);

#ifdef CONFIG_1
void foo(int a, A b, float c, A d) {
  CHECK_EQ(42, a);
  CHECK_EQ(13, b.a);
  CHECK_EQ(23.0f, c);
  CHECK_EQ(81, d.a);
}
#else
int main() {
  foo(42, A(13), 23.0, A(81));
}
#endif
