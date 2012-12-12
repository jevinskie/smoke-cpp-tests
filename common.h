#ifndef COMMON_H_
#define COMMON_H_

extern "C" int printf(const char *fmt, ...);
extern "C" void exit(int code);
#define CHECK(condition) \
  do { \
    if (!(condition)) { \
      printf("Error: '" #condition "' is false!\n"); \
      exit(__LINE__); \
    } \
  } while (0)

#endif  // COMMON_H_
