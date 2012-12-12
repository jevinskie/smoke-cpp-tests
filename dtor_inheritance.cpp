#include "common.h"

extern int base_dtor_calls, derived_dtor_calls;

class Base {
 public:
  ~Base() {
    base_dtor_calls++;
  }
};

class Derived: public Base {
 public:
  ~Derived() {
    derived_dtor_calls++;
  }
};

#ifdef CONFIG_1
void run() {
  Derived d;
}

#else
int base_dtor_calls, derived_dtor_calls;

void run();

int main() {
  run();
  CHECK(base_dtor_calls == 1);
  CHECK(derived_dtor_calls == 1);
}
#endif
