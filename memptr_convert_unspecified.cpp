#include "common.h"

#if defined(_MSC_VER) && !defined(__clang__)
# define CAN_CONVERT_VBASE
#endif

struct Unspecified;
static int Unspecified::*force_unspecified;

struct Base1 {
  int a;
  void foo() { a = 1; }
};

struct Base2 {
  int b;
  void foo() { b = 2; }
};

struct VBase {
  int c;
  void foo() { c = 3; }
};

struct Unspecified : Base1, Base2, virtual VBase {
  int u;
};

typedef void (Unspecified::*UnspecMP)();

UnspecMP convertBase1(void (Base1::*memptr)());
UnspecMP convertBase2(void (Base2::*memptr)());
#ifdef CAN_CONVERT_VBASE
UnspecMP convertVBase(void (VBase::*memptr)());
#endif

#ifdef CONFIG_1
UnspecMP convertBase1(void (Base1::*mp)()) { return mp; }
UnspecMP convertBase2(void (Base2::*mp)()) { return mp; }
#ifdef CAN_CONVERT_VBASE
UnspecMP convertVBase(void (VBase::*mp)()) { return mp; }
#endif
#else

int main() {
  // See that the two compilers agree on the repr after conversion.
  CHECK(convertBase1(&Base1::foo) == &Unspecified::Base1::foo);
  CHECK(convertBase2(&Base2::foo) == &Unspecified::Base2::foo);

  // Call them and see if it works :)
  Unspecified u;
  u.a = u.b = u.c = 0;
  (u.*convertBase1(&Base1::foo))();
  CHECK_EQ(u.a, 1);
  u.a = u.b = u.c = 0;
  (u.*convertBase2(&Base2::foo))();

#ifdef CAN_CONVERT_VBASE
  // Do the vbase stuff last since it's likely to fail.
  CHECK(convertVBase(&VBase::foo) == &Unspecified::VBase::foo);
  CHECK_EQ(u.b, 2);
  u.a = u.b = u.c = 0;
  (u.*convertVBase(&VBase::foo))();
  CHECK_EQ(u.c, 3);
#endif
}

#endif
