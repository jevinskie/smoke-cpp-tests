#include "common.h"

struct A {
  A();
  A(const A &);  // The non-trivial copy ctor matters!
  ~A();
  int val;
};

void foo(A a, A b, A c);
#ifdef CONFIG_1
int next_tmp;
A::A() : val(next_tmp++) {}
A::~A() { CHECK_EQ(val, --next_tmp); }

void foo(A a, A b, A c) { }
#else
int main() {
  foo(A(), A(), A());
}
#endif
