#include "common.h"

// http://llvm.org/PR15058

extern int base_dtor_calls, derived_dtor_calls;

class Base {
 public:
  virtual ~Base();
};

#ifdef CONFIG_1
void call_complete_dtor(Base* obj);

Base::~Base() {
  base_dtor_calls++;
}

class Derived: public Base {
 public:
  virtual ~Derived() {
    derived_dtor_calls++;
  }
};

void run() {
  call_complete_dtor(new Derived);
}

#else
int base_dtor_calls, derived_dtor_calls;

void operator delete (void* ptr) {
  CHECK(!"Shouldn't be called");
}

void call_complete_dtor(Base* obj) {
  void *esp_before = get_esp();
  obj->~Base();
  CHECK_EQ(esp_before, get_esp());
}

void run();

int main() {
  run();
  CHECK_EQ(1, base_dtor_calls);
  CHECK_EQ(1, derived_dtor_calls);
}
#endif
