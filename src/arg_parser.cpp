// (c) Copyright 2016 Josh Wright
#include "util/arg_parser.h"
#include <fstream>
#include <iomanip>
#include <iostream>

namespace util {

using std::string;
using std::unordered_map;

void parse_args(unordered_map<string, string> &config, const int argc,
                const char **argv) {
  /*iterate through every argument,
   * start at 1 to skip the program name as first argument*/
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    /*is this argument a key=value pair?*/
    size_t index = arg.find('=');
    if (index == std::string::npos) {
      /*if not, set it's value to an empty string*/
      config[arg] = "";
    } else {
      std::string lhs = arg.substr(0, index);
      std::string rhs = arg.substr(index + 1, std::string::npos);
      if (lhs == "json") {
        // magic function to read json from file instead of continuing
        std::fstream in(rhs);
        json json_cfg;
        in >> json_cfg;
        for (json::iterator p = json_cfg.begin(); p != json_cfg.end(); p++) {
          if (p.value().is_string()) {
            config[p.key()] = p.value();
          } else {
            config[p.key()] = p.value().dump();
          }
        }

      } else {
        /*if so, set the key and value apropriately*/
        config[lhs] = rhs;
      }
    }
  }
}

void parse_args(std::unordered_map<std::string, std::stringstream> &config,
                const int argc, const char **argv) {
  std::unordered_map<std::string, std::string> config2;
  parse_args(config2, argc, argv);
  for (auto &p : config2) {
    config[p.first] << p.second;
  }
}

void help_printer(const int argc, const char **argv,
                  const std::vector<std::pair<std::string, std::string>> &helps,
                  int column_gap, int parameter_column_width) {
  using std::cout;
  using std::endl;
  using std::setw;

  bool print = false;
  if (argc < 2) {
    print = true;
  } else {
    for (int i = 0; i < argc; i++) {
      std::string arg = argv[i];
      if (arg == "-h" || arg == "--help") {
        print = true;
        break;
      }
    }
  }

  if (print) {
    cout << "usage: " << argv[0] << "<key1>=<value1> <key2>=<value2> ..."
         << endl;

    cout << setw(parameter_column_width) << "key:";
    cout << setw(column_gap) << "";
    cout << "value:";
    cout << endl;

    // TODO automatically determine width
    // TODO wrap after maximum width
    for (auto p : helps) {
      cout << setw(parameter_column_width) << p.first;
      cout << setw(column_gap) << "";
      cout << p.second;
      cout << endl;
    }
    exit(1);
  }
}

arg_parser::arg_parser(const int argc, const char **argv) {
  parse_args(config, argc, argv);
}

void arg_parser::read_bool(bool &val, const std::string &argname) const {
  val = config.find(argname) != config.end();
}
}
