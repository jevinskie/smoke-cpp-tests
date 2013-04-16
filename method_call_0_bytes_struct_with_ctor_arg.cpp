#include "common.h"

struct S {
  S() {}
};

struct Z {
  void foo(S s);
};

#ifdef CONFIG_1
void Z::foo(S s) {
}
#else
int main() {
  void *esp_before = get_esp();
  S s;
  Z z;
  z.foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
