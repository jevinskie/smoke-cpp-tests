// http://llvm.org/PR12070

#include "common.h"

struct Base1 {
  virtual void Virt1();
  int a;
};

struct Simple {
  Simple() { }
  Simple(int m) :member(m) { }
  ~Simple() {
  }
  void NonVirtual();
  int member;
  Base1 non_simple_member;
};

struct Base2 {
  virtual void Virt2();
  int b;
};

struct SingleInheritance : Base1 {
  virtual void Virt1();
  int member;
};

struct MultiInheritance : Base1, Base2 {
  virtual void Virt1();
  virtual void Virt2();
  int member;
};

// I declared these as globals, but I get link errors with clang that way.  It
// will link fine with globals with cl.exe for both configs.  I made this a
// struct to work around the problem.
struct Linkage {
  int Simple::*simple_member;
  int Simple::*simple_null;
  int Base1::*base_member;
  int Base1::*base_null;
  int SingleInheritance::*single_member;
  int SingleInheritance::*single_null;
  int MultiInheritance::*multi_member;
  int MultiInheritance::*multi_null;
};

void foo(Linkage *l);

#ifdef CONFIG_1

void Base1::Virt1() { }
void Base2::Virt2() { }
void SingleInheritance::Virt1() { }
void MultiInheritance::Virt1() { }
void MultiInheritance::Virt2() { }

void foo(Linkage *l) {
  l->simple_member = &Simple::member;
  l->simple_null = 0;
  l->base_member = &Base1::a;
  l->base_null = 0;
  l->single_member = &SingleInheritance::member;
  l->single_null = 0;
  l->multi_member = &MultiInheritance::member;
  l->multi_null = 0;
}
#else
int main() {
  Linkage l;
  foo(&l);

  Simple simple;
  simple.member = 10;
  if (simple.*l.simple_member != 10)
    return 1;
  if (l.simple_null)
    return 2;

  SingleInheritance single;
  single.member = 10;
  if (single.*l.single_member != 10)
    return 3;
  if (l.single_null)
    return 4;

  MultiInheritance multi;
  multi.member = 20;
  if (multi.*l.multi_member != 20)
    return 5;
  if (l.multi_null)
    return 6;

  return 0;
}
#endif
