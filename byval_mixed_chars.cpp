#include "common.h"

struct A {
  A(int a) : a(a) {}
  A(const A &o) : a(o.a) {}
  ~A() {}
  int a;
};

void foo(char a, char b, A c, char d, bool e, int f, bool g);

#ifdef CONFIG_1
void foo(char a, char b, A c, char d, bool e, int f, bool g) {
  CHECK_EQ('A', a);
  CHECK_EQ('B', b);
  CHECK_EQ(42, c.a);
  CHECK_EQ('D', d);
  CHECK_EQ(true, e);
  CHECK_EQ(13, f);
  CHECK_EQ(false, g);
}
#else
int main() {
  foo('A', 'B', A(42), 'D', true, 13, false);
}
#endif
