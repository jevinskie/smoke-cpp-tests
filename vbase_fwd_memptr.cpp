struct A;
struct B;
struct C;
struct D;

extern int B::*memptr;

#ifdef CONFIG_1
int B::*memptr;

void foo() {
  memptr = 0;
}

#else
struct A {
  int a;
};
struct B : virtual A {
  int b;
};
struct C : virtual A {
  int c;
};
struct D : B, C {
  int d;
};
int main() {
  memptr = &B::b;
}
#endif
