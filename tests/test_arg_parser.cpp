// (c) Copyright 2016 Josh Wright

#include "../lib/arg_parser.h"
#include "../lib/debug.h"


/*convenience macro stolen from stackoverflow*/
#define ARRAY_SIZE(a)                               \
  ((sizeof(a) / sizeof(*(a))) /                     \
  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))


int main() {
    using namespace containers;
    {
        std::unordered_map<std::string, std::string> config;
        config["default_one"] = "the_first_default";
        config["override_me"] = "test";
        const char* argv[]{
                "programname",
                "test=asdf",
                "testone",
                "test_two=two",
                "override_me=overridden"
        };
        int argc = ARRAY_SIZE(argv);
        parse_args(config, argc, argv);
        test(config["default_one"] == "the_first_default", "config");
        test(config["test"] == "asdf", "config");
        test(config.find("testone") != config.end(), "config");
        test(config["testone"] == "", "config");
        test(config["test_two"] == "two", "config");
        test(config["override_me"] != "test", "config");
        test(config["override_me"] == "overridden", "config");

        /*printer for debugging*/
//        for (auto &a : config) {
//            std::cout << a.first << " = " << a.second << std::endl;
//        }

    }
    return 0;
}
