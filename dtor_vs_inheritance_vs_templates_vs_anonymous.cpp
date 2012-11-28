struct A {
  ~A() {}
};

template<class T> struct B : A { };
template<class T> struct C : B<T> { };
template<class T> struct D : C<T> { };

#ifndef CONFIG_1
namespace {
  struct s {};
}

int main() {
  D<s> d;
}
#endif
