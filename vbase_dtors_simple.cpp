#include "common.h"

struct Base {
  ~Base();
};

struct Child : virtual Base {
  Child();
  ~Child();
};

extern int base_dtor_calls, child_dtor_calls;

#ifdef CONFIG_1
Child::Child() {}

Child::~Child() {
  CHECK_EQ(0, base_dtor_calls);
  CHECK_EQ(0, child_dtor_calls);
  child_dtor_calls++;
}

#else
int base_dtor_calls, child_dtor_calls;

Base::~Base() {
  CHECK_EQ(0, base_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  base_dtor_calls++;
}

int main() {
  void *old_esp;
  {
    Child c;
    old_esp = get_esp();
  }
  CHECK_EQ(old_esp, get_esp());

  CHECK_EQ(1, base_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
}
#endif
