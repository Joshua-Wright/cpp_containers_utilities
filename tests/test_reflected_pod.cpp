// (c) Copyright 2017 Josh Wright
#include "testing.h"
#include "util/ReflectedPOD.h"

#define ARRAY_SIZE(a)           \
  ((sizeof(a) / sizeof(*(a))) / \
   static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

struct type1 {
  REFLECT_BASE(type1)
  REFLECT_FIELD(type1, size_t, num1)
  REFLECT_FIELD(type1, double, decimal)
  REFLECT_FIELD(type1, std::string, word)
};


int main() {
  {
    type1 instance;
    instance.reflect.set("num1", "1123");
    test(instance.num1 == 1123, "set by reflection");
    instance.decimal = 1.234;
    test(*instance.reflect.get<double>("decimal") == 1.234, "read by reflection");
  }

  // This does not work, because when we construct the struct without the default initializations,
  // the fields do not auto-register with the reflection agent
  // {
  //   type1 instance{util::ReflectedBase("instance"), 123, 1.1, "test"};
  //   test(*instance.reflect.get<double>("decimal") == 1.1, "read when constructed manually");
  // }

  {
    // this will work because the reflection component of basic will be copied into instance,
    // where it will use relative addresses to resolve fields
    type1 basic, instance{basic.reflect, 123, 1.1, "test"};
    test(*instance.reflect.get<double>("decimal") == 1.1, "read when constructed manually");
  }
}
