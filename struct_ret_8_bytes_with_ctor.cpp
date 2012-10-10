// http://llvm.org/PR13676

struct S {
  S() {}
  int a, b;
};

S foo();

#ifdef CONFIG_1
S foo() {
  S ret;
  ret.a = 1;
  ret.b = 2;
  return ret;
}
#else
int main() {
  S s = foo();
  if (s.a != 1)
    return 1;
  if (s.b != 2)
    return 2;
}
#endif
