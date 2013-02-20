#include "common.h"

struct Base { Base(); };

struct Middle : virtual Base {
  Middle();
};

struct Child : Middle {
  Child();
};

extern int base_ctor_calls,
           middle_ctor_calls,
           child_ctor_calls;

#ifdef CONFIG_1
Child::Child() {
  CHECK_EQ(1, base_ctor_calls);
  CHECK_EQ(1, middle_ctor_calls);
  CHECK_EQ(0, child_ctor_calls);
  child_ctor_calls++;
}

#else
int base_ctor_calls,
    middle_ctor_calls,
    child_ctor_calls;

Base::Base() {
  CHECK_EQ(0, base_ctor_calls);
  CHECK_EQ(0, middle_ctor_calls);
  CHECK_EQ(0, child_ctor_calls);
  base_ctor_calls++;
}

Middle::Middle() {
  CHECK_EQ(1, base_ctor_calls);
  CHECK_EQ(0, middle_ctor_calls);
  CHECK_EQ(0, child_ctor_calls);
  middle_ctor_calls++;
}

int main() {
  void *old_esp = get_esp();
  Child c;
  CHECK_EQ(old_esp, get_esp());

  CHECK_EQ(1, base_ctor_calls);
  CHECK_EQ(1, middle_ctor_calls);
  CHECK_EQ(1, child_ctor_calls);
}
#endif
