#include "common.h"

struct BaseLeft { ~BaseLeft(); };
struct BaseRight { ~BaseRight(); };

struct Child : virtual BaseLeft, virtual BaseRight {
  ~Child();
};

extern int base_left_dtor_calls,
           base_right_dtor_calls,
           child_dtor_calls;

#ifdef CONFIG_1
Child::~Child() {
  CHECK_EQ(0, base_left_dtor_calls);
  CHECK_EQ(0, base_right_dtor_calls);
  CHECK_EQ(0, child_dtor_calls);
  child_dtor_calls++;
}

#else
int base_left_dtor_calls,
    base_right_dtor_calls,
    child_dtor_calls;

BaseLeft::~BaseLeft() {
  CHECK_EQ(0, base_left_dtor_calls);
  CHECK_EQ(1, base_right_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  base_left_dtor_calls++;
}

BaseRight::~BaseRight() {
  CHECK_EQ(0, base_left_dtor_calls);
  CHECK_EQ(0, base_right_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  base_right_dtor_calls++;
}

int main() {
  void *old_esp;
  {
    Child c;
    old_esp = get_esp();
  }
  CHECK_EQ(old_esp, get_esp());

  CHECK_EQ(1, base_left_dtor_calls);
  CHECK_EQ(1, base_right_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
}
#endif
