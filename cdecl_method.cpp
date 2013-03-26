#include "common.h"

class C {
 public:
  int __cdecl foo(int a, int b, int c);
};

#ifdef CONFIG_1
int __cdecl C::foo(int a, int b, int c) {
  CHECK_EQ(1, a);
  CHECK_EQ(2, b);
  CHECK_EQ(3, c);
  return 4;
}
#else
int main() {
  C c;
  int x = c.foo(1, 2, 3);
  CHECK_EQ(4, x);
}
#endif
