#include "common.h"
#include <stdarg.h>

extern "C" int vsnprintf(char *buf, memcpy_size_t sz, const char *fmt, va_list ap);
extern "C" int strcmp(const char *a, const char *b);

struct Foo {
  char buf[20];
  virtual void foo(const char *fmt, ...);
};
void bar(Foo *f, void (Foo::*mp)(const char *fmt, ...));

#ifdef CONFIG_1
void bar(Foo *f, void (Foo::*mp)(const char *fmt, ...)) {
  return (f->*mp)("%d %d %d", 1, 2, 3);
}

#else
void Foo::foo(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
}

int main() {
  Foo a;
  bar(&a, &Foo::foo);
  CHECK_EQ(strcmp(a.buf, "1 2 3"), 0);
}
#endif
