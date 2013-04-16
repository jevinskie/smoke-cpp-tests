// http://llvm.org/PR13676
#include "common.h"

struct S {
  int a, b, c, d, e, f;
};

void foo(S s);

#ifdef CONFIG_1
void foo(S s) {
  CHECK_EQ(1, s.a);
  CHECK_EQ(2, s.b);
  CHECK_EQ(3, s.c);
  CHECK_EQ(4, s.d);
  CHECK_EQ(5, s.e);
  CHECK_EQ(6, s.f);
}
#else
int main() {
  S s;
  s.a = 1;
  s.b = 2;
  s.c = 3;
  s.d = 4;
  s.e = 5;
  s.f = 6;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
