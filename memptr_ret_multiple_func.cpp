#include "common.h"

struct B { int b; };
struct C { int c; int f(); };
struct A : B, C { int a; };

int (A::*get_mp())();
#ifdef CONFIG_1
int C::f() {
  return c;
}
int (A::*get_mp())() {
  return &A::f;
}
#else
int main() {
  A a;
  a.c = 42;
  int (A::*mp)() = get_mp();
  int x = (a.*mp)();
  CHECK_EQ(42, x);
}
#endif
