#pragma once

#include "util/debug.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

// This must be the first macro used inside a reflected struct
#define REFLECT_BASE(struct_name) \
  util::ReflectedBase reflect = util::ReflectedBase(#struct_name);

// This must be used for every member of the reflected struct that reflection will apply to
#define REFLECT_FIELD(struct_name, type, name) \
  type name = util::register_member(&name, offsetof(struct_name, name), #name);

namespace util {

struct ReflectedMember {
  std::string name;
  ptrdiff_t offset;
  std::type_index type;
  std::function<void(void *, const std::string &)> read;
};

class ReflectedBase {
  std::string type_name;
  std::vector<ReflectedMember> members;

  void *get_offset(ptrdiff_t offset) {
    return ((uint8_t *)this) + offset;
  }

public:
  ReflectedBase(const std::string &type_name);

  template <typename T>
  void registerMember(ptrdiff_t offset, const std::string &name) {
    members.push_back(
        {name,
         offset,
         typeid(T),
         [](void *addr, const std::string &str) {
           std::stringstream ss(str);
           ss >> *(T *)(addr);
         }});
  };

  template <typename T>
  T *get(const std::string &name) {
    for (auto &member : members) {
      if (member.name == name && member.type == std::type_index(typeid(T))) {
        return (T *)this->get_offset(member.offset);
      }
    }
    return nullptr;
  }

  void set(std::string member_name, std::string value);
};

template <typename T>
T register_member(T *data, uint64_t offset, const std::string &name) {
  ReflectedBase *base = (ReflectedBase *)(((uint8_t *)data) - offset);
  base->registerMember<T>(offset, name);
  return T();
}
};
