class Base {
 public:
  virtual ~Base();

  virtual void a() = 0;
  virtual void b() = 0;
  virtual void c() = 0;
};

#ifdef CONFIG_1
extern int dtor_calls, a_calls, b_calls, c_calls;

void foo(Base* obj);

class Child: public Base {
 public:
  void a() { a_calls++; }
  void b() { b_calls++; }
  void c() { c_calls++; }
};

void run() {
  Child obj;
  foo(&obj);
}

Base::~Base() {
  dtor_calls++;
}

#else
int dtor_calls, a_calls, b_calls, c_calls;

void foo(Base* obj) {
  obj->b();
}

void run();

int main() {
  run();

  if (dtor_calls != 1)
    return 1;
  if (a_calls != 0)
    return 2;
  if (b_calls != 1)
    return 3;
  if (c_calls != 0)
    return 4;
}
#endif
