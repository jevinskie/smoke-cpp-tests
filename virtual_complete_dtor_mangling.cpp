#include "common.h"

extern int base_dtor_calls;

class Base {
 public:
  virtual ~Base();
};

#ifdef CONFIG_1
void call_complete_dtor(Base* obj);

void run() {
  call_complete_dtor(new Base());
}

#else
int base_dtor_calls;

Base::~Base() {
  base_dtor_calls++;
}

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
}
#endif
