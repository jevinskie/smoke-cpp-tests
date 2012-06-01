class Class {
 public:
  void method();

 private:
  int a;
};

#if CONFIG_1
  extern int checker;

  // Builds the class method with one set of flags
  void Class::method() {
    a++;
    checker++;
  }
#else
  int checker;

  int main() {
    Class c;
    c.method();  // And calls it with the other.
    return (checker != 1);
  }
#endif
