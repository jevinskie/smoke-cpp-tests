// http://llvm.org/PR13676

struct S {
  int a, b;
};

class C {
 public:
  S foo();
};

#ifdef CONFIG_1
S C::foo() {
  S ret;
  ret.a = 1;
  ret.b = 2;
  return ret;
}
#else
int main() {
  C c;
  S s = c.foo();
  if (s.a != 1)
    return 1;
  if (s.b != 2)
    return 2;
}
#endif
