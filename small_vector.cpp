// Check that we don't memcpy SmallVec when passing it by value.
// http://llvm.org/PR5064
#include "common.h"

struct SmallVec {
  SmallVec() : ptr(vals) {}

  SmallVec(const SmallVec &o) : ptr(vals) {
    memcpy(vals, o.vals, sizeof(vals));
  }

  static int dtors;
  ~SmallVec() {
    CHECK_EQ(ptr, vals);
    ++dtors;
  }

  int *ptr;
  int vals[10];

};

void foo(SmallVec f);

#ifdef CONFIG_1
int SmallVec::dtors;
void foo(SmallVec f) {
}

#else
int main() {
  foo(SmallVec());
  CHECK_EQ(SmallVec::dtors, 1);
}
#endif
