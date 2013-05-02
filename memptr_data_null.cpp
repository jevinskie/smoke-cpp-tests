#include "common.h"

#ifndef _MSC_VER
# define __single_inheritance
# define __multiple_inheritance
# define __virtual_inheritance
#endif

struct __single_inheritance Single;
struct __multiple_inheritance Multiple;
struct __virtual_inheritance Virtual;
struct Unspecified;

bool testSingle(int Single::*mp);
bool testMultiple(int Multiple::*mp);
bool testVirtual(int Virtual::*mp);
bool testUnspecified(int Unspecified::*mp);

#ifdef CONFIG_1
int Single::* getSingleNull() { return 0; }
int Multiple::* getMultipleNull() { return 0; }

bool testSingle(int Single::*mp) { return mp; }
bool testMultiple(int Multiple::*mp) { return mp; }
bool testVirtual(int Virtual::*mp) { return mp; }
bool testUnspecified(int Unspecified::*mp) { return mp; }

#else

struct Single {
  int foo;
};

struct B1 {
  int foo;
};
struct B2 {
  int foo;
};
struct Multiple : B1, B2 {
  int foo;
};

struct Virtual : virtual B1 {
  int foo;
};

// Force Unspecified to use the unspecified model.
int Unspecified::*g_unspecified_memptr = 0;
struct Unspecified {
  int foo;
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
