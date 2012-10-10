// http://llvm.org/PR13676

struct S {
  int a;
};

S foo();

#ifdef CONFIG_1
S foo() {
  S ret;
  ret.a = 1;
  return ret;
}
#else
int main() {
  S s = foo();
  if (s.a != 1)
    return 1;
}
#endif
