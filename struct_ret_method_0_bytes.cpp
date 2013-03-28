// http://llvm.org/PR13676
#include "common.h"

struct S {
};

class C {
 public:
  S foo();
};

#ifdef CONFIG_1
S C::foo() {
  S ret;
  return ret;
}
#else
int main() {
  C c;
  void *esp_before = get_esp();
  S s = c.foo();
  CHECK_EQ(esp_before, get_esp());
}
#endif
