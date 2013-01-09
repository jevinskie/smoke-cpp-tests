struct Base {
  ~Base() {}
};

template <typename T>
struct Derived : Base {};

namespace {
struct s {};
}

#ifdef CONFIG_1
// This is PR14447.
// Intentionally not doing the #else part.
int main() {
  Derived<s> *d = new Derived<s>;
  delete d;
}
#endif
