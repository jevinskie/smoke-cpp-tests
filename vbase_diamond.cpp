#include "common.h"

// TODO: need vbase support, but memptr representation in MS ABI is:
// {offset in class, offset in vbtable}

struct A {
  int a;
};

struct B : virtual A {
  int b;
};

struct C : virtual A {
  int c;
};

struct D : virtual B, virtual C {
  int d;
};

//struct E : virtual B, virtual C, virtual D {
  //int e;
//};

void foo(D *bp, int B::*memptr);

#ifdef CONFIG_1

void foo(D *bp, int B::*memptr) {
  bp->*memptr = 10;
}

#else
int main() {
  D o;
  // D's layout is:
}
#endif
