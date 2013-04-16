#include "common.h"

struct S {
  S() {}
  S(const struct S &other) {
    x = other.x;
    y = other.y;
  }
  int x, y;
};

struct Z {
  void foo(S);
};

#ifndef CONFIG_1
void Z::foo(S t) {
  CHECK_EQ(0x12345678, t.x);
  CHECK_EQ(0x53452345, t.y);
}
#else
int main() {
  Z z;
  S t;
  t.x = 0x12345678;
  t.y = 0x53452345;
  void *esp_before = get_esp();
  z.foo(t);
  CHECK_EQ(esp_before, get_esp());
}
#endif
