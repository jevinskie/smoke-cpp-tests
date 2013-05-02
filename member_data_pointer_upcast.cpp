// http://llvm.org/PR12070 (wrong)

#include "common.h"

class Base1 {
 public:
  virtual void Virt1();
  int a;
};

class Base2 {
 public:
  virtual void Virt2();
  int b;
};

class MultiInheritance : public Base1, public Base2 {
 public:
  virtual void Virt1();
  virtual void Virt2();
  int member;
};

// I declared these as globals, but I get link errors with clang that way.  It
// will link fine with globals with cl.exe for both configs.  I made this a
// struct to work around the problem.
struct Linkage {
  int MultiInheritance::*multi_member;
  int MultiInheritance::*multi_null;
};

void foo(Linkage *l);

#ifdef CONFIG_1

void Base1::Virt1() { }
void Base2::Virt2() { }
void MultiInheritance::Virt1() { }
void MultiInheritance::Virt2() { }

Base2 *getBase2(MultiInheritance *multi) {
  return multi;
}

void foo(Linkage *l) {
  MultiInheritance m;
  Base2 *b = getBase2(&m);
  b->b = 10;

  int Base2::*base_memptr = &Base2::b;
  m.*base_memptr = 10;
  printf("m.b: %d\n", m.b);

  int MultiInheritance::*multi_memptr;
  multi_memptr = &Base2::b;
  m.*multi_memptr = 20;
  printf("m.b: %d\n", m.b);
}

#else
int main() {
  Linkage l;
  foo(&l);

  return 0;
}
#endif
