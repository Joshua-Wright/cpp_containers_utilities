// (c) Copyright 2016 Josh Wright

#include "testing.h"
#include "util/arg_parser.h"
#include "util/debug.h"

/*convenience macro stolen from stackoverflow*/
#define ARRAY_SIZE(a)             \
    ((sizeof(a) / sizeof(*(a))) / \
     static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))


int main() {
    using namespace util;
    using std::string;
    {
        const char *argv[]{
            "programname",
            "test=asdf",
            "testone",
            "test_two=two",
            "override_me=overridden"};

        int argc = ARRAY_SIZE(argv);
        arg_parser config(argc, argv);

        test(config.read<string>("default_one", "the_first_default") == "the_first_default", "config");
        test(config.read<string>("test") == "asdf", "config");
        test(config.read<string>("testone") == "", "config");
        test(config.read<string>("test_two") == "two", "config");
        test(config.read<string>("override_me") != "test", "config");
        test(config.read<string>("override_me") == "overridden", "config");
    }

    return 0;
}
