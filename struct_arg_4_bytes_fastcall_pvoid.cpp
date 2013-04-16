// http://llvm.org/PR13676
#include "common.h"

struct S {
  void *a;
};

void FASTCALL foo(S s);

#define VALUE ((void*)4213)

#ifdef CONFIG_1
void FASTCALL foo(S s) {
  CHECK_EQ(VALUE, s.a);
}
#else
int main() {
  S s;
  s.a = VALUE;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
