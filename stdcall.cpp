#include "common.h"

extern int cnt;
void STDCALL foo();
extern "C" void STDCALL bar();

#ifdef CONFIG_1
void STDCALL foo() {
  cnt = 42;
}

void STDCALL bar() {
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
