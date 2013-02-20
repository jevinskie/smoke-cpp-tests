#include "common.h"

struct Base { Base(); };

struct MiddleLeft : virtual Base {
  MiddleLeft();
};

struct MiddleRight : virtual Base {
  MiddleRight();
};

struct Child : MiddleLeft, MiddleRight {
  Child();
};

extern int base_ctor_calls,
           middle_left_ctor_calls, middle_right_ctor_calls,
           child_ctor_calls;

#ifdef CONFIG_1
Child::Child() {
  CHECK_EQ(1, base_ctor_calls);
  CHECK_EQ(1, middle_left_ctor_calls);
  CHECK_EQ(1, middle_right_ctor_calls);
  CHECK_EQ(0, child_ctor_calls);
  child_ctor_calls++;
}

#else
int base_ctor_calls,
    middle_left_ctor_calls, middle_right_ctor_calls,
    child_ctor_calls;

Base::Base() {
  CHECK_EQ(0, base_ctor_calls);
  CHECK_EQ(0, middle_left_ctor_calls);
  CHECK_EQ(0, middle_right_ctor_calls);
  CHECK_EQ(0, child_ctor_calls);
  base_ctor_calls++;
}

MiddleLeft::MiddleLeft() {
  CHECK_EQ(1, base_ctor_calls);
  CHECK_EQ(0, middle_left_ctor_calls);
  CHECK_EQ(0, middle_right_ctor_calls);
  CHECK_EQ(0, child_ctor_calls);
  middle_left_ctor_calls++;
}

MiddleRight::MiddleRight() {
  CHECK_EQ(1, base_ctor_calls);
  CHECK_EQ(1, middle_left_ctor_calls);
  CHECK_EQ(0, middle_right_ctor_calls);
  CHECK_EQ(0, child_ctor_calls);
  middle_right_ctor_calls++;
}

int main() {
  void *old_esp = get_esp();
  Child c;
  CHECK_EQ(old_esp, get_esp());

  CHECK_EQ(1, base_ctor_calls);
  CHECK_EQ(1, middle_left_ctor_calls);
  CHECK_EQ(1, middle_right_ctor_calls);
  CHECK_EQ(1, child_ctor_calls);
}
#endif
