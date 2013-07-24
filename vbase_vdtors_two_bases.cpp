#include "common.h"

struct BaseLeft {
  virtual ~BaseLeft();
};

struct BaseRight {
  virtual ~BaseRight();
};

struct Child : virtual BaseLeft, virtual BaseRight {
  virtual ~Child();
};

extern int base_left_dtor_calls,
           base_right_dtor_calls,
           child_dtor_calls, operator_delete_calls;

void destroy(BaseRight *);

#ifdef CONFIG_1
Child::~Child() {
  CHECK_EQ(0, base_left_dtor_calls);
  CHECK_EQ(0, base_right_dtor_calls);
  CHECK_EQ(0, child_dtor_calls);
  child_dtor_calls++;
}

void destroy(BaseRight *obj) {
  delete obj;
}

#else
int base_left_dtor_calls,
    base_right_dtor_calls,
    child_dtor_calls,
    operator_delete_calls;

BaseLeft::~BaseLeft() {
  CHECK_EQ(0, base_left_dtor_calls);
  CHECK_EQ(1, base_right_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  CHECK_EQ(0, operator_delete_calls);
  base_left_dtor_calls++;
}

BaseRight::~BaseRight() {
  CHECK_EQ(0, base_left_dtor_calls);
  CHECK_EQ(0, base_right_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  base_right_dtor_calls++;
}

void operator delete (void* ptr) {
  operator_delete_calls++;
}

int main() {
  void *old_esp;
  Child *c = new Child;
  old_esp = get_esp();
  destroy(c);
  CHECK_EQ(old_esp, get_esp());

  CHECK_EQ(1, base_left_dtor_calls);
  CHECK_EQ(1, base_right_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  CHECK_EQ(1, operator_delete_calls);
}
#endif
