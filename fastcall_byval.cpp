#include "common.h"
struct A {
  int a, b;
  A() : a(13), b(42) {}
  A(const A &o) : a(o.a), b(o.b) {}
  ~A() {
    CHECK_EQ(a, 13);
    CHECK_EQ(b, 42);
  }
};
void __fastcall f(A a, A b, int c, int d, int e);
#ifdef CONFIG_1
void __fastcall f(A a, A b, int c, int d, int e) {
  CHECK_EQ(c, 1);
  CHECK_EQ(d, 2);
  CHECK_EQ(e, 3);
  CHECK_EQ(a.a, 13);
  CHECK_EQ(a.b, 42);
  CHECK_EQ(b.a, 13);
  CHECK_EQ(b.b, 42);
}
#else
int main() {
  f(A(), A(), 1, 2, 3);
}
#endif
