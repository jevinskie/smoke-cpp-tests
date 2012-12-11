extern int cnt;
void __stdcall foo();
extern "C" void __stdcall bar();

#ifdef CONFIG_1
void __stdcall foo() {
  cnt = 42;
}

void __stdcall bar() {
  cnt = 13;
}

#else
int cnt = 10;

int main() {
  foo();
  if (cnt != 42)
    return 1;

  bar();
  if (cnt != 13)
    return 2;
}
#endif
