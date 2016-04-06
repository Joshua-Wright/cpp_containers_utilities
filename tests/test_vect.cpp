// (c) Copyright 2015 Josh Wright

#include "vect.h"
#include "debug.h"

int main(int argc, char const *argv[]) {
  using namespace containers;

  {
    /*constructor*/
    vect<int, 3> test1;
    vect<int, 5> vect2{1, 2, 3, 4, 5};
    vect<int, 5> vect3 = {1, 2, 3, 4, 5};
  }
  {
    /*element access*/
    vect<int, 3> vect2 = {1, 2, 3};
    test(vect2[0] == 1, "element access");
    test(vect2[1] == 2, "element access");
    test(vect2[2] == 3, "element access");
  }
  {
    /*equality*/
    vect<int, 5> vect1{1, 2, 3, 4, 5};
    vect<int, 5> vect2{1, 2, 3, 4, 5};
    vect<int, 5> vect3{1, 2, 3, 4, 9};
    test(vect1 == vect2, "equality");
    test(vect2 == vect1, "equality");
    test(vect2 != vect3, "equality");
  }
  {
    /*compound assignment operators*/
    vect<int, 5> vect1a{1, 2, 3, 4, 5};
    vect<int, 5> vect1b{1, 2, 3, 4, 5};
    vect<int, 5> vect1c{1, 2, 3, 4, 5};
    vect<int, 5> vect1d{1, 2, 3, 4, 5};
    vect1a += 2;
    vect1b -= 2;
    vect1c *= 2;
    vect1d /= 2;
    vect<int, 5> r1{3, 4, 5, 6, 7};
    vect<int, 5> r2{-1, 0, 1, 2, 3};
    vect<int, 5> r3{2, 4, 6, 8, 10};
    vect<int, 5> r4{0, 1, 1, 2, 2};
    test(vect1a == r1, "+=");
    test(vect1b == r2, "-=");
    test(vect1c == r3, "*=");
    test(vect1d == r4, "/=");
  }

  return 0;
}
