// http://llvm.org/PR13676
#include "common.h"

struct S {
  double a;
};

void foo(S s);

#ifdef CONFIG_1
void foo(S s) {
  CHECK_EQ(1234.0, s.a);
}
#else
int main() {
  S s;
  s.a = 1234.0;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
