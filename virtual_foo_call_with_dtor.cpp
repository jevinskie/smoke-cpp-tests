#include "common.h"

extern int foo_calls;

class Base {
 public:
  virtual void foo();
  virtual ~Base();
};

#ifdef CONFIG_1
void call_foo(Base* obj);

void run() {
  call_foo(new Base());
  // Intentionally leak the object.
}

#else
int foo_calls;

void Base::foo() {
  foo_calls++;
}

Base::~Base() {
  CHECK(!"Shouldn't be called");
}

void operator delete (void* ptr) {
  CHECK(!"Shouldn't be called");
}

void call_foo(Base* obj) {
  obj->foo();
}

void run();

int main() {
  run();
  CHECK_EQ(1, foo_calls);
}
#endif
