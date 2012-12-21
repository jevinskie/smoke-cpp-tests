#include "common.h"

extern int dtor_calls;

struct Class {
  ~Class();
};

#ifdef CONFIG_1
Class::~Class() {
  dtor_calls++;
}

#else
int dtor_calls;

void operator delete (void *ptr) {
  CHECK(!"Shouldn't be called");
}

int main() {
  Class *obj = new Class;
  obj->~Class();
  CHECK_EQ(1, dtor_calls);
}
#endif
