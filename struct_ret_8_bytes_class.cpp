#include "common.h"

class S;
S foo();
class S {
 public:
  int a, b;
  friend S foo();
  friend int main();
};

#ifdef CONFIG_1
S foo() {
  S ret;
  ret.a = 1;
  ret.b = 2;
  return ret;
}
#else
int main() {
  S s = foo();
  CHECK_EQ(1, s.a);
  CHECK_EQ(2, s.b);
}
#endif
