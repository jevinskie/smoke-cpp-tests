#include "common.h"

struct Base {
  virtual ~Base();
};

struct Child : virtual Base {
  virtual ~Child();
};

extern int base_dtor_calls, child_dtor_calls, operator_delete_calls;

void destroy(Base *);

#ifdef CONFIG_1
Child::~Child() {
  CHECK_EQ(0, base_dtor_calls);
  CHECK_EQ(0, child_dtor_calls);
  child_dtor_calls++;
}

void destroy(Base *obj) {
  delete obj;
}

#else
int base_dtor_calls, child_dtor_calls, operator_delete_calls;

Base::~Base() {
  CHECK_EQ(0, base_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  CHECK_EQ(0, operator_delete_calls);
  base_dtor_calls++;
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

  CHECK_EQ(1, base_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  CHECK_EQ(1, operator_delete_calls);
}
#endif
