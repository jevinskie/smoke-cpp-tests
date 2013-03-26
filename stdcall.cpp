#include "common.h"

extern int cnt;
void __stdcall foo();
extern "C" void __stdcall bar();

#ifdef CONFIG_1
void __stdcall foo() {
  cnt = 42;
}

void __stdcall bar() {
  cnt = 13;
}

#else
int cnt = 10;

int main() {
  foo();
  CHECK_EQ(42, cnt);

  bar();
  CHECK_EQ(13, cnt);
}
#endif
