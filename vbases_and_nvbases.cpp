#include "common.h"

struct A {
  int a;
};

struct B : virtual A {
  int b;
};

struct Z {
  int z;
};

struct C : virtual Z, B {
  int c;
};

void check(C *obj);

#ifdef CONFIG_1
void check(C *obj) {
  CHECK_EQ(1, obj->a);
  CHECK_EQ(2, obj->b);
  CHECK_EQ(3, obj->z);
  CHECK_EQ(4, obj->c);
}
#else
int main() {
  C c;
  c.a = 1;
  c.b = 2;
  c.z = 3;
  c.c = 4;
  check(&c);
}
#endif
