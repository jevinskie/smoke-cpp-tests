extern int cnt;
void __stdcall foo();

#ifdef CONFIG_1
void __stdcall foo() {
  cnt = 42;
}

#else
int cnt = 10;

int main() {
  foo();
  return (cnt == 42) ? 0 : 1;
}
#endif
