// http://llvm.org/PR13676
#include "common.h"

struct S {
};

void foo(S s);

#ifdef CONFIG_1
void foo(S s) {
}
#else
int main() {
  S s;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
