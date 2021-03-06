// http://llvm.org/PR13676
#include "common.h"

struct S {
  float a;
  float b;
};

void foo(S s);

#ifdef CONFIG_1
void foo(S s) {
  CHECK_EQ(1234.0f, s.a);
  CHECK_EQ(4321.0f, s.b);
}
#else
int main() {
  S s;
  s.a = 1234.0f;
  s.b = 4321.0f;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
