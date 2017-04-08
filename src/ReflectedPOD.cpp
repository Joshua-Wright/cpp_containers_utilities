#include "util/ReflectedPOD.h"

namespace util {

ReflectedBase::ReflectedBase(const std::string &type_name) : type_name(type_name){};

void ReflectedBase::set(std::string member_name, std::string value) {
  for (auto &member : members) {
    if (member.name == member_name) {
      member.read(get_offset(member.offset), value);
      return;
    }
  }
}
};
