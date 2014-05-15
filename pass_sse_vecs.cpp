#include "common.h"
#include <xmmintrin.h>

void __cdecl foo(__m128 a,
                 __m128 b,
                 __m128 c,
                 __m128 d);
#ifdef CONFIG_1
void __cdecl foo(__m128 a,
                 __m128 b,
                 __m128 c,
                 __m128 d) {
  CHECK_EQ(__alignof(a), 16);
  CHECK_EQ(__alignof(b), 16);
  CHECK_EQ(__alignof(c), 16);
  CHECK_EQ(__alignof(d), 16);
  CHECK_EQ(intptr_t(&a) & 15, 0);
  CHECK_EQ(intptr_t(&b) & 15, 0);
  CHECK_EQ(intptr_t(&c) & 15, 0);
  CHECK_EQ(intptr_t(&d) & 15, 0);
}
#else
int main() {
  __m128 a = _mm_setzero_ps();
  __m128 b = a, c = a, d = a;
  foo(a, b, c, d);
}
#endif
