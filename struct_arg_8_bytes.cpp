// http://llvm.org/PR13676
#include "common.h"

struct S {
  int a, b;
};

void foo(S s);

#ifdef CONFIG_1
void foo(S s) {
  CHECK_EQ(1, s.a);
  CHECK_EQ(2, s.b);
}
#else
int main() {
  S s;
  s.a = 1;
  s.b = 2;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
