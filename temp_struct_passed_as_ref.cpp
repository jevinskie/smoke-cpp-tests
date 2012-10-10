// This has been failing in Clang, see http://llvm.org/PR13761

struct S {
  S();
  int a, b;
};

#ifdef CONFIG_1
  S::S() : a(1), b(2) {}
#else
  int foo(const struct S &s) {
    if (s.a != 1)
      return 1;
    if (s.b != 2)
      return 2;
    return 0;
  }

  int main() {
    return foo(S());
  }
#endif
