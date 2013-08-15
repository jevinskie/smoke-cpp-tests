#include "common.h"

struct S {
  S();
  ~S();
  int x;
};
extern S s;

#ifdef CONFIG_1
S::S() : x(1) { }

S::~S() {
  exit(0);
}

S s;

#else
int main() {
  CHECK_EQ(1, s.x);
  return 1;
}
#endif
