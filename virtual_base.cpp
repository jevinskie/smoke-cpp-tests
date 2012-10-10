extern "C" void exit(int);

inline void oops() {
  exit(1);
}

class Base {
 public:
  Base() {}
  ~Base() {}

  void foo(void *real_this) {
    if (real_this != this) oops();
  }

  int base_field;
};

class Child: public virtual Base {
 public:
  Child() {}
  void bar(void *real_c, void *real_b) {
    if (real_c != this) oops();
    foo(real_b);
  }

  int child_field;
};

void *get_real_c();
void *get_real_b();

#ifdef CONFIG_1
Child c;

void *get_real_c() {
  return &c;
}

void *get_real_b() {
  return static_cast<Base*>(&c);
}
#else

void run();

extern Child c;

int main() {
  c.bar(get_real_c(), get_real_b());
}
#endif
