class Base1 {
 public:
  virtual void foo() {}

  int a;
};

class Base2 {
 public:
  virtual void bar(void *T, int A, int B, int C) {}

  int b;
};

class Child: public Base1, public Base2 {
 public:
  // This overrides the right child's method,
  // hence requires this adjustment (e.g. thunk)
  virtual void bar(void *T, int A, int B, int C);

  int c;
};

#ifdef CONFIG_1
extern "C" void _exit(int);

#define CHECK2(cond,exitcode) \
    do { \
      if (!(cond)) { \
        _exit(exitcode); \
      } \
    } while (0)

void Child::bar(void *T, int A, int B, int C) {
  CHECK2(A == 1, 1);
  CHECK2(B == 2, 2);
  CHECK2(C == 3, 3);
  CHECK2(T == this, 4);
}

#else

int main() {
  Child obj;
  obj.bar(&obj, 1, 2, 3);
}
#endif
