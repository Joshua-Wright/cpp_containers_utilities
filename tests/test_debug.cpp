// (c) Copyright 2015 Josh Wright

#include "../lib/debug.h"

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
    debug_log_notype(var);
    debug_log_type(var);
    debug_log(&var);
    debug_log_notype(var2);
    debug_log_type(var2);
    debug_log(&var2);
    debug_log(var.c_str());
    debug_log(     5);
    debug_log(5     );
    debug_log((float) 123.431243213123123213123123123);
    debug_log((int) 123.431243213123123213123123123);
    debug_log(123.431243213123123213123123123);
    debug_log('a');
    debug_log('as');
    debug_log('asd');
    debug_log('asdf');
    debug_log("asdf");
    debug_log(__test);
    debug_log(&__test);
    debug_log(basename("test"));
    debug_log(basename("/test"));
    debug_log(basename("/path/to/test"));

    return 0;
}
