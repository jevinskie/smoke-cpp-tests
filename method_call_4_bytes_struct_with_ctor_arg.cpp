#include "common.h"

struct S {
  S() {}
  int x;
};

struct Z {
  void foo(S);
};

#ifndef CONFIG_1
void Z::foo(S t) {
  CHECK_EQ(0x12345678, t.x);
}
#else
int main() {
  Z z;
  S t;
  t.x = 0x12345678;
  void *esp_before = get_esp();
  z.foo(t);
  CHECK_EQ(esp_before, get_esp());
}
#endif
