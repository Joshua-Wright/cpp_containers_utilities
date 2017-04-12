#include "testing.h"
#include "util/debug.h"
#include "util/struct_tuple.h"
#include <iostream>
#include <unordered_map>

using namespace std;

struct C {
  int i;
  float f;
  std::string s;
};

ADAPT_FIELDS(C, i, f, s)

int main() {
  unordered_map<string, string> values{
      {"i", "123"},
      {"f", "123.875"},
      {"s", "asdf"},
  };

  C c = read<C>(values);
  test(c.i == 123, "read int");
  test(c.f == 123.875, "read float");
  test(c.s == "asdf", "read string");
  test(std::string(get_struct_name(c)) == "C", "name of type");
}
