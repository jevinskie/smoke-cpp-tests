#include "common.h"

#pragma pack(push, 1)
struct S {
  char a, b, c;
};
#pragma pack(pop)

void foo(S s);

#ifdef CONFIG_1
void foo(S s) {
  CHECK_EQ(1, s.a);
  CHECK_EQ(2, s.b);
  CHECK_EQ(3, s.c);
}
#else
int main() {
  CHECK_EQ(3, sizeof(S));
  S s;
  s.a = 1;
  s.b = 2;
  s.c = 3;
  void *esp_before = get_esp();
  foo(s);
  CHECK_EQ(esp_before, get_esp());
}
#endif
