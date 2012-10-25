class Base1 {
 public:
  virtual void foo();

  int a;
};

class Base2 {
 public:
  virtual void bar();

  int b;
};

class Child: public Base1, public Base2 {
 public:
  virtual void fill();

  int c;
};

#ifdef CONFIG_1
// When this is compiled with CL, link fails to find the vftables when linking
// with Clang-generated other half of the code.
// FIXME: Probably Clang should emit the vftables even then they are not used?

void Base1::foo() { }

void Base2::bar() { }

void Child::fill() {
  a = 1;
  b = 2;
  c = 3;
}

#else
int main() {
  Child obj;
  obj.a = obj.b = obj.c = 42;
  obj.fill();

  if (obj.a != 1)
    return 1;
  if (obj.b != 2)
    return 2;
  if (obj.c != 3)
    return 3;
}
#endif
