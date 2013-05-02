#include "common.h"

extern int ctor_calls;

struct Class {
  Class();
};

#ifdef CONFIG_1
Class::Class() {
  ctor_calls++;
}

#else
int ctor_calls;

int main() {
  Class *obj = new Class;
  CHECK_EQ(1, ctor_calls);
}
#endif
