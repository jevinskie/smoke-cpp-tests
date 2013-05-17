#include "common.h"

__declspec(selectany) int x = 5;

int *foo();
#ifdef CONFIG_1
int *foo() { return &x; }
#else
int main() {
  CHECK_EQ(&x, foo());
}
#endif
