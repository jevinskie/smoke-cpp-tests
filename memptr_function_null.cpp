#include "common.h"

struct __single_inheritance Single;
struct __multiple_inheritance Multiple;
struct __virtual_inheritance Virtual;
struct Unspecified;

bool testSingle(void (Single::*mp)());
bool testMultiple(void (Multiple::*mp)());
bool testVirtual(void (Virtual::*mp)());
bool testUnspecified(void (Unspecified::*mp)());

#ifdef CONFIG_1

bool testSingle(void (Single::*mp)()) { return mp; }
bool testMultiple(void (Multiple::*mp)()) { return mp; }
bool testVirtual(void (Virtual::*mp)()) { return mp; }
bool testUnspecified(void (Unspecified::*mp)()) { return mp; }

#else

struct Single {
  virtual void foo();
};

struct B1 {
  virtual void foo();
};
struct B2 {
  virtual void foo();
};
struct Multiple : B1, B2 {
  virtual void foo();
};

struct Virtual : virtual B1 {
  virtual void foo();
};

// Force Unspecified to use the unspecified model.
void (Unspecified::*g_unspecified_memptr)() = 0;
struct Unspecified {
  virtual void foo();
};

int main() {
  CHECK_EQ(false, testSingle(0));
  CHECK_EQ(false, testMultiple(0));
  CHECK_EQ(false, testVirtual(0));
  CHECK_EQ(false, testUnspecified(0));

  CHECK_EQ(true, testSingle(&Single::foo));
  CHECK_EQ(true, testMultiple(&Multiple::foo));
  CHECK_EQ(true, testVirtual(&Virtual::foo));
  CHECK_EQ(true, testUnspecified(&Unspecified::foo));

  // We only need to test the method pointer (slot 0) to know if the memptr is
  // non-null.  Full equality requires more comparisons.
  CHECK_EQ(false, testUnspecified(g_unspecified_memptr));
}

#endif
