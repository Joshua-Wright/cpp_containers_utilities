#pragma once
#include <sstream>
#include <type_traits>

template <size_t I, typename T>
struct struct_element;

template <typename T>
struct struct_element_count;

template <size_t idx, typename T>
const char *getname(const T &);

template <typename T>
const char *get_struct_name(const T &);

template <size_t idx, typename T>
typename struct_element<idx, T>::type &get(T &);

template <size_t I, typename T, typename Map>
void read_field(T &t, Map &m) {
  std::stringstream ss(m[getname<I>(t)]);
  ss >> get<I>(t);
}

template <typename T, size_t I = struct_element_count<T>().count() - 1, typename Map>
typename std::enable_if<(sizeof(T), I == 0), T>::type
read(Map &m) {
  T t;
  read_field<I>(t, m);
  return t;
}

template <typename T, size_t I = struct_element_count<T>().count() - 1, typename Map>
typename std::enable_if<(sizeof(T), I != 0), T>::type
read(Map &m) {
  T t = read<T, I - 1, Map>(m);
  read_field<I>(t, m);
  return t;
}

#define DEFINE_GET(T, m, I)                    \
  template <>                                  \
  struct struct_element<I, const T> {          \
    typedef const decltype(T::m) type;         \
  };                                           \
  template <>                                  \
  struct struct_element<I, T> {                \
    typedef decltype(T::m) type;               \
  };                                           \
  template <>                                  \
  inline struct_element<I, const T>::type &    \
  get<I, const T>(const T &t) { return t.m; }; \
  template <>                                  \
  inline struct_element<I, T>::type &          \
      get<I, T>(T & t) { return t.m; };        \
  template <>                                  \
  inline const char *                          \
  getname<I, T>(const T &) { return #m; };

#define DEFINE_COUNT(T, I)         \
  template <>                      \
  struct struct_element_count<T> { \
    inline constexpr size_t        \
    count() { return I; };         \
  };

#define DEFINE_NAME(T) \
  template <>          \
  inline const char *  \
  get_struct_name<T>(const T &) { return #T; };

#define ADAPT_FIELDS(T, ...)         \
  DEFINE_COUNT(T, NARG(__VA_ARGS__)) \
  DEFINE_NAME(T)                     \
  FIELDS(T, __VA_ARGS__)

#define FIELDS_MULTIPLE(T, N, ...) __FIELDS_##N(T, __VA_ARGS__)
// the following is necessary to make sure the processor has a chance to evaluate NARG16
#define _FIELDS_MULTIPLE(T, N, ...) FIELDS_MULTIPLE(T, N, __VA_ARGS__)
#define FIELDS(T, ...) _FIELDS_MULTIPLE(T, NARG(__VA_ARGS__), __VA_ARGS__)


#define __FIELDS_0(T)
#define __FIELDS_1(T, a1) \
  DEFINE_GET(T, a1, 0)    \
  __FIELDS_0(T)
#define __FIELDS_2(T, a1, a2) \
  DEFINE_GET(T, a2, 1)        \
  __FIELDS_1(T, a1)
#define __FIELDS_3(T, a1, a2, a3) \
  DEFINE_GET(T, a3, 2)            \
  __FIELDS_2(T, a1, a2)
#define __FIELDS_4(T, a1, a2, a3, a4) \
  DEFINE_GET(T, a4, 3)                \
  __FIELDS_3(T, a1, a2, a3)
#define __FIELDS_5(T, a1, a2, a3, a4, a5) \
  DEFINE_GET(T, a5, 4)                    \
  __FIELDS_4(T, a1, a2, a3, a4)
#define __FIELDS_6(T, a1, a2, a3, a4, a5, a6) \
  DEFINE_GET(T, a6, 5)                        \
  __FIELDS_5(T, a1, a2, a3, a4, a5)
#define __FIELDS_7(T, a1, a2, a3, a4, a5, a6, a7) \
  DEFINE_GET(T, a7, 6)                            \
  __FIELDS_6(T, a1, a2, a3, a4, a5, a6)
#define __FIELDS_8(T, a1, a2, a3, a4, a5, a6, a7, a8) \
  DEFINE_GET(T, a8, 7)                                \
  __FIELDS_7(T, a1, a2, a3, a4, a5, a6, a7)
#define __FIELDS_9(T, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
  DEFINE_GET(T, a9, 8)                                    \
  __FIELDS_8(T, a1, a2, a3, a4, a5, a6, a7, a8)
#define __FIELDS_10(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
  DEFINE_GET(T, a10, 9)                                         \
  __FIELDS_9(T, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define __FIELDS_11(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) \
  DEFINE_GET(T, a11, 10)                                             \
  __FIELDS_10(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
#define __FIELDS_12(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) \
  DEFINE_GET(T, a12, 11)                                                  \
  __FIELDS_11(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11)
#define __FIELDS_13(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) \
  DEFINE_GET(T, a13, 12)                                                       \
  __FIELDS_12(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12)
#define __FIELDS_14(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) \
  DEFINE_GET(T, a14, 13)                                                            \
  __FIELDS_13(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13)
#define __FIELDS_15(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) \
  DEFINE_GET(T, a15, 14)                                                                 \
  __FIELDS_14(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14)
#define __FIELDS_16(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) \
  DEFINE_GET(T, a16, 15)                                                                      \
  __FIELDS_15(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15)
#define __FIELDS_17(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) \
  DEFINE_GET(T, a17, 16)                                                                           \
  __FIELDS_16(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16)
#define __FIELDS_18(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18) \
  DEFINE_GET(T, a18, 17)                                                                                \
  __FIELDS_17(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17)
#define __FIELDS_19(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19) \
  DEFINE_GET(T, a19, 18)                                                                                     \
  __FIELDS_18(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18)
#define __FIELDS_20(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20) \
  DEFINE_GET(T, a20, 19)                                                                                          \
  __FIELDS_19(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19)
#define __FIELDS_21(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21) \
  DEFINE_GET(T, a21, 20)                                                                                               \
  __FIELDS_20(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20)
#define __FIELDS_22(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22) \
  DEFINE_GET(T, a22, 21)                                                                                                    \
  __FIELDS_21(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21)
#define __FIELDS_23(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23) \
  DEFINE_GET(T, a23, 22)                                                                                                         \
  __FIELDS_22(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22)
#define __FIELDS_24(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24) \
  DEFINE_GET(T, a24, 23)                                                                                                              \
  __FIELDS_23(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23)
#define __FIELDS_25(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25) \
  DEFINE_GET(T, a25, 24)                                                                                                                   \
  __FIELDS_24(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24)
#define __FIELDS_26(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26) \
  DEFINE_GET(T, a26, 25)                                                                                                                        \
  __FIELDS_25(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25)
#define __FIELDS_27(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27) \
  DEFINE_GET(T, a27, 26)                                                                                                                             \
  __FIELDS_26(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26)
#define __FIELDS_28(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28) \
  DEFINE_GET(T, a28, 27)                                                                                                                                  \
  __FIELDS_27(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27)
#define __FIELDS_29(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29) \
  DEFINE_GET(T, a29, 28)                                                                                                                                       \
  __FIELDS_28(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28)
#define __FIELDS_30(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30) \
  DEFINE_GET(T, a30, 29)                                                                                                                                            \
  __FIELDS_29(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29)
#define __FIELDS_31(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31) \
  DEFINE_GET(T, a31, 30)                                                                                                                                                 \
  __FIELDS_30(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30)
#define __FIELDS_32(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32) \
  DEFINE_GET(T, a32, 31)                                                                                                                                                      \
  __FIELDS_31(T, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31)
