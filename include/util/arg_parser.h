// (c) Copyright 2016 Josh Wright
#pragma once

#include "struct_tuple.h"
#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace util {

void parse_args(std::unordered_map<std::string, std::stringstream> &config,
                const int argc, const char **argv);

void parse_args(std::unordered_map<std::string, std::string> &config,
                const int argc, const char **argv);

template <typename T>
T parse_args(const int argc, const char **argv, T t = T()) {
  std::unordered_map<std::string, std::string> config;
  parse_args(config, argc, argv);
  t = read<T>(config, t);
  return t;
};

class arg_parser {
  std::unordered_map<std::string, std::string> config;

public:
  arg_parser(const int argc, const char **argv);

  template <typename T> T read(const std::string &argname, T def = T()) const {
    auto it = config.find(argname);
    if (it != config.end()) {
      std::stringstream ss2(it->second);
      ss2 >> def;
    }
    return def;
  }

  /**
   *
   * @tparam T type of arg being read
   * @tparam U optional, type of literal supplied (for convenience)
   * @param val target to read into
   * @param argname name of argument on command line
   * @param def default value (optional)
   */
  template <typename T, typename U = T>
  void read_into(T &val, const std::string &argname, U def = U()) const {
    auto it = config.find(argname);
    if (it != config.end()) {
      std::stringstream ss2(it->second);
      ss2 >> val;
    } else {
      val = def;
    }
  }

  void read_bool(bool &val, const std::string &argname) const;
};

void help_printer(const int argc, const char **argv,
                  const std::vector<std::pair<std::string, std::string>> &helps,
                  int column_gap = 4, int parameter_column_width = 20);
}
