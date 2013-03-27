// This crashes when compiled by cl.exe, but I think it's conformant C++.

extern "C" int printf(const char *fmt, ...);

// header unspecified_fwd.h:
struct Unspecified;

#ifdef CONFIG_1
// header unrelated.h:
// Lock in sizeof(void (Unspecified::*)()).
void (Unspecified::*g_memptr)();
#endif

// header unspecified.h:
struct Unspecified {
  void Func() { }
};

#ifdef CONFIG_1
// source file a.cpp

void CallUnspecifiedMemptr(Unspecified *u, int *a, void (Unspecified::*memptr)()) {
  (u->*memptr)();
  memptr = 0;
  printf("*a: %d\n", *a);
}

#else
// source file b.cpp

void CallUnspecifiedMemptr(Unspecified *u, int *a, void (Unspecified::*memptr)());

int main() {
  Unspecified u;
  int a = 123;
  CallUnspecifiedMemptr(&u, &a, &Unspecified::Func);
}

#endif
