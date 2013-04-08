#include "common.h"

#define c const
#define v volatile

template <typename T>
void *mynew() {
  return (void *)new T();
}

typedef void *(*VoidFn)();
void fill_table1();
extern VoidFn table1[4];

#ifdef CONFIG_1
VoidFn table1[4];

void fill_table1() {
  table1[0] = (VoidFn)&mynew<    int>;
  table1[1] = (VoidFn)&mynew<c   int>;
  table1[2] = (VoidFn)&mynew<  v int>;
  table1[3] = (VoidFn)&mynew<c v int>;
}
#else

int main() {
  fill_table1();
  CHECK_EQ((VoidFn)table1[0], (VoidFn)&mynew<    int>);
  CHECK_EQ((VoidFn)table1[1], (VoidFn)&mynew<c   int>);
  CHECK_EQ((VoidFn)table1[2], (VoidFn)&mynew<  v int>);
  CHECK_EQ((VoidFn)table1[3], (VoidFn)&mynew<c v int>);
  // Attempting uniqueness
  CHECK(table1[0] != table1[1]);
  CHECK(table1[1] != table1[2]);
  CHECK(table1[2] != table1[3]);
}
#endif
