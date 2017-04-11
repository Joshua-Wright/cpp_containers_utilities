#pragma once


struct string_wrapper {
  const char *str;
};

// template <typename T, const char... name_>
template <typename T, const char *name_>
class named_value {
  T val;

public:
  template <typename U>
  named_value(U u) : val(u) {}

  template <typename... Args>
  named_value(Args... args) : val(args...) {}

  template <typename U>
  named_value &operator=(const U &other) {
    val = other;
    return *this;
  }
  const char *name() const {
    return name_;
  }

  operator T() {
    return val;
  }

  // static constexpr char name[]{name_...};
};
