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

inline bool check_eq_impl(int a, const char *a_str,
                          int b, const char *b_str,
                          unsigned int line_no) {
  if (!(a == b)) {
    printf("Error: %s != %s (%d != %d) at line %d.\n",
           a_str, b_str, a, b, line_no);
    return false;
  }
  return true;
}

inline bool check_eq_impl(float a, const char *a_str,
                          float b, const char *b_str,
                          unsigned int line_no) {
  if (!(a == b)) {
    printf("Error: %s != %s (%f != %f) at line %d.\n",
           a_str, b_str, a, b, line_no);
    return false;
  }
  return true;
}

inline bool check_eq_impl(double a, const char *a_str,
                          double b, const char *b_str,
                          unsigned int line_no) {
  if (!(a == b)) {
    printf("Error: %s != %s (%lf != %lf) at line %d.\n",
           a_str, b_str, a, b, line_no);
    return false;
  }
  return true;
}

inline bool check_eq_impl(void *a, const char *a_str,
                          void *b, const char *b_str,
                          unsigned int line_no) {
  if (!(a == b)) {
    printf("Error: %s != %s (0x%p != 0x%p) at line %d.\n",
           a_str, b_str, a, b, line_no);
    return false;
  }
  return true;
}

template<typename T>
bool check_eq_impl(T a, const char *a_str,
                   T b, const char *b_str,
                   unsigned int line_no) {
  if (!(a == b)) {
    printf("Error: %s != %s (0x%p != 0x%p) at line %d.\n",
           a_str, b_str, reinterpret_cast<void*>(a), reinterpret_cast<void*>(b), line_no);
    return false;
  }
  return true;
}

#define CHECK_EQ(expected,actual) \
  do { \
    if (!check_eq_impl((actual), #actual, (expected), #expected, __LINE__)) \
      exit(1 + (__LINE__ % 100)); \
  } while (0)

inline bool check_ne_impl(void *a, const char *a_str,
                          void *b, const char *b_str,
                          unsigned int line_no) {
  if (!(a != b)) {
    printf("Error: %s == %s (0x%p == 0x%p) at line %d.\n",
           a_str, b_str, a, b, line_no);
    return false;
  }
  return true;
}

#define CHECK_NE(expected,actual) \
  do { \
    if (!check_ne_impl((actual), #actual, (expected), #expected, __LINE__)) \
      exit(1 + (__LINE__ % 100)); \
  } while (0)

#ifdef _MSC_VER
# define CDECL __cdecl
# define STDCALL __stdcall
# define FASTCALL __fastcall
#else
# define CDECL    // Already cdecl by default.
# define STDCALL  __attribute__((stdcall))
# define FASTCALL __attribute__((fastcall))
#endif

extern "C" void *_AddressOfReturnAddress();

inline void* get_esp() {
#if !defined(_MSC_VER) || defined(__has_feature)
  return __builtin_frame_address(0);
#else
  return _AddressOfReturnAddress();
#endif
}

#endif  // COMMON_H_
