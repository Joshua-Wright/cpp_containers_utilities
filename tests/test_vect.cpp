// (c) Copyright 2015 Josh Wright

#include "vect.h"
#include "debug.h"

int main(int argc, char const *argv[]) {
  using namespace containers;

  {/*element access*/
    vect<int, 5> vect1{1, 2, 3, 4, 5};
    vect<int, 3> vect2 = {1, 2, 3};
    vect<int, 5> vect3;
    test(vect2[0] == 1, "element access");
    test(vect2[1] == 2, "element access");
    test(vect2[2] == 3, "element access");
    vect2[1] = 9;
    test(vect2[1] == 9, "element access");
    test(std::all_of(vect3.begin(), vect3.end(), [](int a) { return a == 0; }),
         "default constructor");
  }
  {/*equality*/
    vect<int, 5> vect1{1, 2, 3, 4, 5};
    vect<int, 5> vect2{1, 2, 3, 4, 5};
    vect<int, 5> vect3{1, 2, 3, 4, 9};
    test(vect1 == vect2, "equality");
    test(vect2 == vect1, "equality");
    test(vect2 != vect3, "equality");
  }
  {
    /*copy assignment*/
    vect<int, 2> vect1{1, 2};
    vect<int, 2> vect2{4, 5};
    test(vect1 != vect2, "constructor");
    vect1 = vect2;
    test(vect1 == vect2, "copy assignment");
  }
  {/*compound assignment operators*/
    vect<int, 5> vect1a{1, 2, 3, 4, 5};
    vect<int, 5> vect1b{1, 2, 3, 4, 5};
    vect<int, 5> vect1c{1, 2, 3, 4, 5};
    vect<int, 5> vect1d{1, 2, 3, 4, 5};
    vect<int, 5> vect1e{1, 2, 3, 4, 5};
    vect1a += 2;
    vect1b -= 2;
    vect1c *= 2;
    vect1d /= 2;
    vect1e %= 2;
    vect<int, 5> r1{3, 4, 5, 6, 7};
    vect<int, 5> r2{-1, 0, 1, 2, 3};
    vect<int, 5> r3{2, 4, 6, 8, 10};
    vect<int, 5> r4{0, 1, 1, 2, 2};
    vect<int, 5> r5{1, 0, 1, 0, 1};
    test(vect1a == r1, "+=");
    test(vect1b == r2, "-=");
    test(vect1c == r3, "*=");
    test(vect1d == r4, "/=");
    test(vect1e == r5, "%=");
  }
  {/*infix operators*/
    vect<int, 5> vect1a{1, 2, 3, 4, 5};
    vect<int, 5> out1{6, 7, 8, 9, 10};
    vect<int, 5> out2{-4, -3, -2, -1, 0};
    vect<int, 5> out3{5, 10, 15, 20, 25};
    vect<int, 5> out4{0, 0, 1, 1, 1};
    vect<int, 5> out5{1, 2, 0, 1, 2};
    /*left to right*/
    test(out1 == vect1a + 5, "+");
    test(out2 == vect1a - 5, "-");
    test(out3 == vect1a * 5, "*");
    test(out4 == vect1a / 3, "/");
    test(out5 == vect1a % 3, "%");
    /*and reverse*/
    test(out1 == 5 + vect1a, "+");
    test(out3 == 5 * vect1a, "*");
    vect<int, 5> out6{9, 8, 7, 6, 5};
    vect<int, 5> out7{100, 50, 33, 25, 20};
    test(out6 == 10 - vect1a, "-");
    test(out7 == 100 / vect1a, "/");
  }
  {/*vector to vector operations*/
    vect<int, 5> vect1a{1, 2, 3, 4, 5};
    vect<int, 5> vect1b{10, 9, 8, 7, 6};
    vect<int, 5> out1{11, 11, 11, 11, 11};/*+*/
    vect<int, 5> out2a{-9, -7, -5, -3, -1};/*-*/
    vect<int, 5> out2b{9, 7, 5, 3, 1};/*-*/
    vect<int, 5> out3{10, 18, 24, 28, 30};/***/
    vect<int, 5> out4a{0, 0, 0, 0, 0};/*/*/
    vect<int, 5> out4b{10, 4, 2, 1, 1};/*/*/
    vect<int, 5> out5a{1, 2, 3, 4, 5};/*%*/
    vect<int, 5> out5b{0, 1, 2, 3, 1};/*%*/
    vect<int, 5> zero{0, 0, 0, 0, 0};/*-*/
    vect<int, 5> one{1, 1, 1, 1, 1};/*-*/
    test(vect1a + vect1b == out1, "+");
    test(vect1a - vect1b == out2a, "-");
    test(vect1b - vect1a == out2b, "-");
    test(vect1a * vect1b == out3, "*");
    test(vect1a / vect1b == out4a, "/");
    test(vect1b / vect1a == out4b, "/");
    test(vect1a % vect1b == out5a, "%");
    test(vect1b % vect1a == out5b, "%");
    test(vect1b - vect1b == zero, "%");
    test(vect1b / vect1b == one, "%");
  }
  {/*norm*/
    vect<double, 3> v1{1, 2, 3};
    test(v1.norm2() == 1 + 2 * 2 + 3 * 3, "norm");
    test(v1.norm() == std::sqrt(1 + 2 * 2 + 3 * 3), "norm");
  }
  {/*pow*/
    vect<double, 3> v1{1, 2, 3};
    vect<double, 3> o1{1, 4, 9};
    test(v1.pow(2) == o1, "pow");
  }
  {/*avg*/
    vect<double, 3> v1{1, 2, 3};
    test(v1.avg() == 2, "avg");
  }
  {/*typecast*/
    vect<double, 3> v1{1, 2.123, 3.0 / 2};
    vect<int, 3> v2 = v1;
    test(v2[0] == 1, "typecast on constructor");
    test(v2[1] == 2, "typecast on constructor");
    test(v2[2] == 1, "typecast on constructor");
    vect<double, 3> out1{1, 2.123 * 2, 1.5};
    test(v1 * v2 == out1, "typecast");
  }

  return 0;
}
