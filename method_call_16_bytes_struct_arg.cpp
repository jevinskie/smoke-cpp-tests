#include "common.h"

struct S {
  int x, y, z, w;
};

struct Z {
  void foo(S);
};

#ifdef CONFIG_1
void Z::foo(S t) {
  CHECK_EQ(0x12345678, t.x);
  CHECK_EQ(0x53452345, t.w);
}
#else
int main() {
  Z z;
  S t;
  t.x = 0x12345678;
  t.w = 0x53452345;
  void *esp_before = get_esp();
  z.foo(t);
  CHECK_EQ(esp_before, get_esp());
}
#endif
