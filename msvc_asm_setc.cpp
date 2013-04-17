#include "common.h"

int foo(int a, int b);

#ifdef CONFIG_1
int foo(int a, int b) {
  __asm {
    mov eax, a
    mov ebx, b
    add eax, ebx
    // Works with setb
    setc al
    movzx eax, al
    mov a, eax
  };
  return a;
}
#else

int main() {
  int r = foo(1, 0);
  CHECK(r == 0);
  r = foo(50, -1);
  CHECK(r == 1);
}
#endif
