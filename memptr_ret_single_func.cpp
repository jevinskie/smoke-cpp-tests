#include "common.h"

struct A {
  int a;
  int b;
  int f();
};

int (A::*get_mp())();
#ifdef CONFIG_1
int A::f() {
  return b;
}
int (A::*get_mp())() {
  return &A::f;
}
#else
int main() {
  A a;
  a.b = 42;
  int (A::*mp)() = get_mp();
  int x = (a.*mp)();
  CHECK_EQ(42, x);
}
#endif
