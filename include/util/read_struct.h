#pragma once
#include <functional>
#include <sstream>
#include <string>
#include <vector>


struct struct_field {
  std::string name;
  std::function<std::string(void *)> get;
  std::function<void(void *, const std::string &)> set;
};

template <typename T>
std::vector<struct_field> get_fields();

template <typename T, typename U, size_t offset>
struct_field make_accessor(std::string name) {
  return struct_field{
      name,
      [name](void *v) {
        uint8_t *p = (uint8_t *)v;
        p += offset;
        U *u = (U *)p;
        std::stringstream ss;
        ss << *u;
        return ss.str();
      },
      [name](void *v, const std::string &val) {
        std::stringstream ss(val);
        uint8_t *p = (uint8_t *)v;
        p += offset;
        U *u = (U *)p;
        ss >> *u;
      },
  };
}

// template <typename T>
// class base_struct_field {
// public:
//   virtual std::string name() = 0;
//   virtual std::string get(T *) = 0;
//   virtual void set(T *, const std::string &) = 0;
// };

// template <typename T, typename U, size_t offset>
// class struct_field : public base_struct_field<T> {
//   const std::string _name;

// public:
//   struct_field(const std::string &v) : _name(v){};

//   virtual std::string name() { return _name; };
//   virtual std::string get(T *t) {
//     uint8_t *p = (uint8_t *)t;
//     p += offset;
//     U *u = p;
//     std::stringstream ss;
//     *u >> ss;
//     return ss.str();
//   };
//   virtual void set(T *t, const std::string &val) {
//     std::stringstream ss(val);
//     uint8_t *p = (uint8_t *)t;
//     p += offset;
//     U *u = p;
//     ss >> *u;
//   };
// };

// template <typename T>
// std::vector<base_struct_field<T> *> get_fields();
