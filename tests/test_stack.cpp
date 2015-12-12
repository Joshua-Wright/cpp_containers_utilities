// (c) Copyright 2015 Josh Wright
#include <cassert>
#include "../lib/stack.h"

int main(int argc, char const *argv[]) {
    using namespace containers;
    stack<int> st;
    assert(st.empty());
    st.push(5);
    st.push(6);
    st.push(7);
    int a = 1234;
    assert(!st.empty());
    assert(st.pop() == 7);
    assert(st.pop() == 6);
    st.push(a);
    assert(st.pop() == 1234);
    assert(st.pop() == 5);
    assert(st.empty());

    return 0;
}
