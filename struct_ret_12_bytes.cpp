// http://llvm.org/PR13676

struct S {
  int a, b, c;
};

S foo();

#ifdef CONFIG_1
S foo() {
  S ret;
  ret.a = 1;
  ret.b = 2;
  ret.c = 3;
  return ret;
}
#else
int main() {
  S s = foo();
  if (s.a != 1)
    return 1;
  if (s.b != 2)
    return 2;
  if (s.c != 3)
    return 3;
}
#endif
