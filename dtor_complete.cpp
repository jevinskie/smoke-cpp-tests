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
int dtor_calls, operator_delete_calls;

void operator delete (void *ptr) {
  operator_delete_calls++;
}

int main() {
  Class *obj = new Class;
  obj->~Class();
  if (dtor_calls != 1)
    return 1;
  if (operator_delete_calls != 0)
    return 2;
}
#endif
