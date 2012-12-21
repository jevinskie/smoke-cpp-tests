#include "common.h"

class Base {
 public:
  virtual ~Base();

  virtual void a() = 0;
  virtual void b() = 0;
  virtual void c() = 0;
};

#ifdef CONFIG_1
extern int dtor_calls, a_calls, b_calls, c_calls;

void foo(Base* obj);

class Child: public Base {
 public:
  void a() { a_calls++; }
  void b() { b_calls++; }
  void c() { c_calls++; }
};

void run() {
  Child obj;
  foo(&obj);
}

Base::~Base() {
  dtor_calls++;
}

#else
int dtor_calls, a_calls, b_calls, c_calls;

void foo(Base* obj) {
  obj->b();
}

void run();

int main() {
  run();

  CHECK_EQ(1, dtor_calls);
  CHECK_EQ(0, a_calls);
  CHECK_EQ(1, b_calls);
  CHECK_EQ(0, c_calls);
}
#endif
