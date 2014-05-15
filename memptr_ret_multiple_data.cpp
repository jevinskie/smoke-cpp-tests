#include "common.h"

struct B { int b; };
struct C { int c; };
struct A : B, C { int a; };

int A::*get_mp();
#ifdef CONFIG_1
int A::*get_mp() {
  return &A::a;
}
#else
int main() {
  A a;
  a.a = 42;
  int A::*mp = get_mp();
  int x = a.*mp;
  CHECK_EQ(42, x);
}
#endif
