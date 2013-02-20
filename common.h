#ifndef COMMON_H_
#define COMMON_H_

extern "C" int printf(const char *fmt, ...);
extern "C" void exit(int code);

#define CHECK(condition) \
  do { \
    if (!(condition)) { \
      printf("Error: '" #condition "' is false at line %d!\n", __LINE__); \
      exit(__LINE__); \
    } \
  } while (0)

#define CHECK_EQ(expected,actual) \
  do { \
    if ((expected) != (actual)) { \
      printf("Error: " #actual " != " #expected \
             " (0x%p != 0x%p) at line %d.\n", \
             (void*)(actual), (void*)(expected), __LINE__); \
      exit(__LINE__); \
    } \
  } while (0)

extern "C" void *_AddressOfReturnAddress();

inline void* get_esp() {
#if !defined(_MSC_VER) || defined(__has_feature)
  return __builtin_frame_address(0);
#else
  return _AddressOfReturnAddress();
#endif
}

#endif  // COMMON_H_
