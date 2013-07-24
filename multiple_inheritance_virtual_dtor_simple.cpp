#include "common.h"

extern int base1_dtor_calls, base2_dtor_calls, child_dtor_calls,
           operator_delete_calls;

class Base1 {
 public:
  virtual void foo() {}
  virtual ~Base1();

  int a;
};

class Base2 {
 public:
  virtual void bar() {}
  virtual ~Base2();

  int b;
};

class Child: public Base1, public Base2 {
 public:
  void fill();
  virtual ~Child();

  int c;
};

void destroy(Child *obj);

#ifdef CONFIG_1
int base1_dtor_calls, base2_dtor_calls, child_dtor_calls, operator_delete_calls;

void destroy(Child *obj) {
  delete obj;
}

#else
Child::~Child() {
  CHECK_EQ(0, base1_dtor_calls);
  CHECK_EQ(0, base2_dtor_calls);
  CHECK_EQ(0, child_dtor_calls);
  child_dtor_calls++;
}

Base2::~Base2() {
  CHECK_EQ(0, base1_dtor_calls);
  CHECK_EQ(0, base2_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  base2_dtor_calls++;
}

Base1::~Base1() {
  CHECK_EQ(0, base1_dtor_calls);
  CHECK_EQ(1, base2_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  base1_dtor_calls++;
}

void operator delete (void* ptr) {
  operator_delete_calls++;
}

int main() {
  Child *obj = new Child;
  destroy(obj);

  CHECK_EQ(1, base1_dtor_calls);
  CHECK_EQ(1, base2_dtor_calls);
  CHECK_EQ(1, child_dtor_calls);
  CHECK_EQ(1, operator_delete_calls);
}
#endif
