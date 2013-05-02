#include <stdlib.h>

// The point of this test is to try different dllimport settings for the CRT
// with /MD, /MT, etc.

void *foo();

#ifdef CONFIG_1
void *foo() {
  return malloc(10);
}

#else
int main() {
  void *p = foo();
  free(p);
}

#endif
