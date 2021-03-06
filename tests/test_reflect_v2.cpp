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
  int defaulted;
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
  c.defaulted = 5;
  c = read(values, c);
  test(c.defaulted == 5, "don't clobber non-existing values");

  // to json
  json j = c;
  test(j == c, "to json");
  test(j["i"] == 123, "to json");

  // from json
  C c2 = R"(
  {
    "i": 432,
    "f": 123.125,
    "s": "a string"
  }
  )"_json;
  test(c2.i == 432, "from json");
  test(c2.f == 123.125, "from json");
  test(c2.s == "a string", "from json");
}
