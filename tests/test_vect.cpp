// (c) Copyright 2015-2017 Josh Wright

#include "testing.h"
#include "util/debug.h"
#include "util/vect.h"

int main() {
  using namespace util;

  { /*element access*/
    vect<int, 5> vect1{1, 2, 3, 4, 5};
    vect<int, 3> vect2 = {1, 2, 3};
    vect<int, 5> vect3;
    vect<int, 5> vect4(5);
    test(vect2[0] == 1, "element access");
    test(vect2[1] == 2, "element access");
    test(vect2[2] == 3, "element access");
    vect2[1] = 9;
    test(vect2[1] == 9, "element access");
    test(std::all_of(vect3.begin(), vect3.end(), [](int a) { return a == 0; }),
         "default constructor");
    test(std::all_of(vect4.begin(), vect4.end(), [](int a) { return a == 5; }),
         "filer constructor");
  }
  { /*equality*/
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
  { /*compound assignment operators*/
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
  { /*compound assignment operators for vectors*/
    vect<int, 5> vect0{1, 2, 3, 4, 5};
    vect<int, 5> vect1a{1, 2, 3, 4, 5};
    vect<int, 5> vect1b{1, 2, 3, 4, 5};
    vect<int, 5> vect1c{1, 2, 3, 4, 5};
    vect<int, 5> vect1d{1, 2, 3, 4, 5};
    vect<int, 5> vect1e{1, 2, 3, 4, 5};
    vect1a += vect0;
    vect1b -= vect0;
    vect1c *= vect0;
    vect1d /= vect0;
    vect1e %= vect0;
    vect<int, 5> r1{2, 4, 6, 8, 10};
    vect<int, 5> r2{0, 0, 0, 0, 0};
    vect<int, 5> r3{1, 4, 9, 16, 25};
    vect<int, 5> r4{1, 1, 1, 1, 1};
    vect<int, 5> r5{0, 0, 0, 0, 0};
    test(vect1a == r1, "+=");
    test(vect1b == r2, "-=");
    test(vect1c == r3, "*=");
    test(vect1d == r4, "/=");
    test(vect1e == r5, "%=");
  }
  { /*infix operators*/
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
  { /*vector to vector operations*/
    vect<int, 5> vect1a{1, 2, 3, 4, 5};
    vect<int, 5> vect1b{10, 9, 8, 7, 6};
    vect<int, 5> out1{11, 11, 11, 11, 11};  /*+*/
    vect<int, 5> out2a{-9, -7, -5, -3, -1}; /*-*/
    vect<int, 5> out2b{9, 7, 5, 3, 1};      /*-*/
    vect<int, 5> out3{10, 18, 24, 28, 30};  /***/
    vect<int, 5> out4a{0, 0, 0, 0, 0};      /*/*/
    vect<int, 5> out4b{10, 4, 2, 1, 1};     /*/*/
    vect<int, 5> out5a{1, 2, 3, 4, 5};      /*%*/
    vect<int, 5> out5b{0, 1, 2, 3, 1};      /*%*/
    vect<int, 5> zero{0, 0, 0, 0, 0};       /*-*/
    vect<int, 5> one{1, 1, 1, 1, 1};        /*-*/
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
  { /*norm*/
    vect<double, 3> v1{1, 2, 3};
    test(v1.norm2() == 1 + 2 * 2 + 3 * 3, "norm");
    test(v1.norm() == std::sqrt(1 + 2 * 2 + 3 * 3), "norm");
  }
  { /*pow*/
    vect<double, 3> v1{1, 2, 3};
    vect<double, 3> o2{1, 2, 3};
    vect<double, 3> o1{1, 4, 9};
    test(v1.pow(2) == o1, "pow");
    test(v1 == o2, "pow");
  }
  { /*avg*/
    vect<double, 3> v1{1, 2, 3};
    test(v1.avg() == 2, "avg");
  }
  { /*typecast*/
    vect<double, 3> v1{1, 2.123, 3.0 / 2};
    vect<int, 3> v2 = v1;
    test(v2[0] == 1, "typecast on constructor");
    test(v2[1] == 2, "typecast on constructor");
    test(v2[2] == 1, "typecast on constructor");
    vect<double, 3> out1{1, 2.123 * 2, 1.5};
    test(v1 * v2 == out1, "typecast");
  }
  { /*cross product 3d*/
    vect<int, 3> in1{1, 2, 3};
    vect<int, 3> in2{9, 8, 7};
    vect<int, 3> out1{-10, 20, -10};
    vect<int, 3> zero(0);
    test(crossP(in1, in2) == out1, "cross product");
    test(crossP(in2, in1) == -1 * out1, "cross product");
    test(crossP(in1, in2) == -1 * crossP(in2, in1), "cross product");
    test(crossP(in2, in2) == zero, "cross product");
    test(crossP(in1, in1) == zero, "cross product");
  }
  { /*cross product 3d*/
    vect<int, 2> in1{1, 2};
    vect<int, 2> in2{9, 8};
    vect<int, 3> out1{0, 0, -10};
    vect<int, 3> zero(0);
    test(crossP(in1, in2) == out1, "cross product");
    test(crossP(in2, in1) == -1 * out1, "cross product");
    test(crossP(in1, in2) == -1 * crossP(in2, in1), "cross product");
    test(crossP(in2, in2) == zero, "cross product");
    test(crossP(in1, in1) == zero, "cross product");
  }
  { /*distance*/
    vect<double, 3> in1{1, 8, 2};
    vect<double, 3> in2{1, 7, 2};
    test(in1.dist(in2) == 1, "distance");
  }

  { /*test memory layout*/
    struct test_mem {
      size_t a;
      size_t b;
      size_t c;
      size_t d;
    };

    size_t test_values[] = {1, 45, 32, 45};
    size_t *vals = new size_t[4];
    std::copy_n((size_t *)&test_values, 4, vals);
    vect<size_t, 4> vect1a = *reinterpret_cast<vect<size_t, 4> *>(vals);
    vect<size_t, 4> vect1b(vals);

    test_mem test_mem1;
    test_mem1.a = test_values[0];
    test_mem1.b = test_values[1];
    test_mem1.c = test_values[2];
    test_mem1.d = test_values[3];
    vect<size_t, 4> vect2a = *reinterpret_cast<vect<size_t, 4> *>(&test_mem1);
    vect<size_t, 4> vect2b(reinterpret_cast<size_t *>(&test_mem1));

    /*these don't work*/
    //    vect<size_t, 4> vect3 = reinterpret_cast<vect<size_t, 4>>(test_mem1);
    //    vect<size_t, 4> vect4 = (vect<size_t, 4>)(test_mem1);

    for (int i = 0; i < 4; i++) {
      test(vals[i] == vect1a[i], "reinterpret cast");
      test(vals[i] == vect1b[i], "reinterpret cast");
      test(vals[i] == vect2a[i], "reinterpret cast");
      test(vals[i] == vect2b[i], "reinterpret cast");
    }
  }

  return 0;
}
