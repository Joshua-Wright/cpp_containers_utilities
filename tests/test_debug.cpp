// (c) Copyright 2016 Josh Wright

#include "util/debug.h"

void test(bool value, std::string msg) {
    if (!value) {
        std::cerr << msg << std::endl;
    }
}

int main() {
    test(true, "This should succeed and not show");
    bool variable_that_is_false = false;
    bool variable_that_is_true = true;
    test(false, "This outght to fail");
    test(variable_that_is_true, "This should succeed and not show");
    test(!variable_that_is_false, "This should succeed and not show");
    test(variable_that_is_false, "This outght to fail");
    test(!variable_that_is_true, "This outght to fail");

    std::string var = "asdf";
    int var2 = 1234;
    DEBUG_LOG_NOTYPE(var);
    DEBUG_LOG_TYPE(var);
    DEBUG_LOG(&var);
    DEBUG_LOG_NOTYPE(var2);
    DEBUG_LOG_NOTYPE(var2);
    DEBUG_LOG(&var2);
    DEBUG_LOG(var.c_str());
    DEBUG_LOG(5);
    DEBUG_LOG(5);
    DEBUG_LOG((float)123.431243213123123213123123123);
    DEBUG_LOG((int)123.431243213123123213123123123);
    DEBUG_LOG(123.431243213123123213123123123);
    DEBUG_LOG('a');
    DEBUG_LOG('as');
    DEBUG_LOG('asd');
    DEBUG_LOG('asdf');
    DEBUG_LOG("asdf");
    DEBUG_LOG(main);
    DEBUG_LOG(&main);
    DEBUG_LOG(basename("test"));
    DEBUG_LOG(basename("/test"));
    DEBUG_LOG(basename("/path/to/test"));
    DEBUG_LOG(typeid(5).name());

    return 0;
}
