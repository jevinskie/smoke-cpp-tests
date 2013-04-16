#include "common.h"

struct S {
  S();
  char x;
};

struct Z {
  void foo(S s);
};

#ifdef CONFIG_1
void Z::foo(S s) {
  CHECK_EQ(42, s.x);
}
#else
int main() {
  void *esp_before = get_esp();
  S s;
  s.x = 42;
  Z z;
  z.foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
