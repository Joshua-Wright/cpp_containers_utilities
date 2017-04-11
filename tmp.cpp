// #include "testing.h"
#include "util/debug.h"
#include "util/read_struct.h"
#include <iostream>
#include <tuple>

struct C {
  int i;
  float f;
};


#define ACCESSOR(struct_t, field) \
  make_accessor<struct_t, decltype(struct_t::field), offsetof(struct_t, field)>(#field)

template <>
inline std::vector<struct_field> get_fields<C>() {
  return std::vector<struct_field>{
      // make_accessor<C, decltype(C::i), offsetof(C, i)>("i"),
      // make_accessor<C, float, offsetof(C, f)>("f"),
      ACCESSOR(C, i),
      ACCESSOR(C, f),
  };
}

template <size_t I, typename T>
struct struct_element;

template <typename T>
struct struct_element_count;

template <size_t idx, typename T>
const char *getname(const T &);

template <size_t idx, typename T>
typename struct_element<idx, T>::type &get(T &);


#define DEFINE_GET(T, m, I)             \
  template <>                           \
  struct struct_element<I, T> {         \
    typedef decltype(T::m) type;        \
  };                                    \
  template <>                           \
  inline struct_element<I, T>::type &   \
      get<I, T>(T & t) { return t.m; }; \
  template <>                           \
  inline const char *                   \
  getname<I, T>(const T &) { return #m; };

#define ADAPT_FIELDS_2(T, f0, f1)           \
  template <>                               \
  struct struct_element_count<T> {          \
    constexpr size_t count() { return 2; }; \
  };                                        \
  DEFINE_GET(T, f0, 0)                      \
  DEFINE_GET(T, f1, 1)

ADAPT_FIELDS_2(C, i, f)


template <typename T, size_t cout = struct_element_count<T>::count()>
void pretty_print(const T &) {
  std::cout << "struct{";
  std::cout << "}";
}

template <size_t I, typename T>
void __pretty_print_field(const T &t) {
  std::cout << get<I>(t) << ", ";
  __pretty_print_field<I - 1>(t);
};
template <0, typename T>
void __pretty_print_field<0, T>(const T &t) {
  std::cout << get<0>(t);
};


int main() {
  using namespace std;
  KV(&C::i);
  KV(&C::f);
  C c = {0};
  KV(c.*(&C::i));
  auto fields = get_fields<C>();
  for (auto field : fields) {
    cout << field.name << std::endl;
  }
  cout << fields[0].get(&c) << endl;
  fields[0].set(&c, "4");
  cout << fields[0].get(&c) << endl;

  KV(get<0>(c));
  KV(get<0>(c) = 8);
  KV(get<0>(c));
  KV(getname<0>(c));
}
