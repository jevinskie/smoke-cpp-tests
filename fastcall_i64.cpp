#include "common.h"

void __fastcall f(unsigned long long a, int b);
#ifdef CONFIG_1
void __fastcall f(unsigned long long a, int b) {
  CHECK_EQ(b, 42);
  unsigned long long aa = 0x4444444444444444ULL;
  CHECK_EQ(memcmp(&a, &aa, sizeof(a)), 0);
}
#else
int main() {
  f(0x4444444444444444ULL, 42);
}
#endif
