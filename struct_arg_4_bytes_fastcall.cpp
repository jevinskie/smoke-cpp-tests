// http://llvm.org/PR13676
#include "common.h"

struct S {
  int a;
};

void FASTCALL foo(S s);

#ifdef CONFIG_1
void FASTCALL foo(S s) {
  CHECK_EQ(1, s.a);
}
#else
int main() {
  S s;
  s.a = 1;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
