extern int cnt;
void __stdcall foo();

#ifdef CONFIG_1
void __stdcall foo() {
  cnt = 42;
}

#else
int cnt = 10;

int main() {
  void (__stdcall *ptr)() = 0;
  ptr = foo;
  (*ptr)();
  return (cnt == 42) ? 0 : 1;
}
#endif
