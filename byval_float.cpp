#include "common.h"
struct A { float a; };
void f(A a);
#ifdef CONFIG_1
void f(A a) {
  // Floats are pretty weird, but these better be bit identical.
  float b = 42.13;
  CHECK_EQ(memcmp(&a.a, &b, sizeof(b)), 0);
}
#else
int main() {
  A a;
  a.a = 42.13;
  f(a);
}
#endif
