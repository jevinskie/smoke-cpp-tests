#include "common.h"

struct A {
  A();
  A(const A &);  // The non-trivial copy ctor matters!
  ~A();
  int a;
};

void foo(A a, A b, A c);
#ifdef CONFIG_1
void *tmps_constructed[3];
int next_tmp;
A::A() {
  CHECK_EQ(next_tmp < 3, 1);
  tmps_constructed[next_tmp++] = (void *)this;
}
A::~A() {
  void *last_tmp = tmps_constructed[--next_tmp];
  CHECK_EQ(last_tmp, (void *)this);
}

void foo(A a, A b, A c) { }
#else
int main() {
  foo(A(), A(), A());
}
#endif
