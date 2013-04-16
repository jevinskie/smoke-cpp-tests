// http://llvm.org/PR13676
#include "common.h"

struct S {
  void *a, *b;
};

void FASTCALL foo(S s);

#define VALUE ((void*)4213)
#define VALUE2 ((void*)8756)

#ifdef CONFIG_1
void FASTCALL foo(S s) {
  CHECK_EQ(VALUE, s.a);
  CHECK_EQ(VALUE2, s.b);
}
#else
int main() {
  S s;
  s.a = VALUE;
  s.b = VALUE2;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
