// http://llvm.org/PR13488

class A{
 public:
  virtual ~A();
};

#ifdef CONFIG_1
// Defines a vftable.
A::~A() {}

#else
// Uses a vftable; may define one as well.
// Gives a link error if the two vftables are different.
int main() {
  A a;
}

#endif
