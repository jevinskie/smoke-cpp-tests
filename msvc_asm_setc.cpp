#include "common.h"

int foo(int a, int b);

#ifdef CONFIG_1
int foo(int a, int b) {
# if defined(_MSC_VER) && defined(_M_IX86)
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
#else
  // For gcc.
  unsigned ua = a, ub = b;
  return ua + ub < ua;
#endif
}
#else

int main() {
  int r = foo(1, 0);
  CHECK(r == 0);
  r = foo(50, -1);
  CHECK(r == 1);
}
#endif
