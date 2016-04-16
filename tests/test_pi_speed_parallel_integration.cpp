// (c) Copyright 2015 Josh Wright
#include <iostream>
#include <vector>
#include <quadmath.h>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <algorithm>

int main(int argc, char const *argv[]) {
  using namespace std::chrono;
//  using std::sqrt;
//  typedef __float128 double;

  const int parallels = 10;
  const __float128 step = 1e-8;
  std::vector<__float128> sums(parallels, 0);


  high_resolution_clock::time_point start = high_resolution_clock::now();
#pragma omp parallel for
  for (int i = 0; i < parallels; i++) {

    __float128 sum = 0;
    if (i == 0) {
      sum = -1;
    }
    for (__float128 x = 1.0 * i / parallels;
         x < (1.0 * i + 1) / parallels; x += step) {
      sum += 2 * sqrtq(1 - x * x);
    }
    sums[i] = sum;
  }
  high_resolution_clock::time_point end = high_resolution_clock::now();
  auto time = (end - start).count();

  int wid = 15;
  int digits = 15;

  sums.push_back(0);
  __float128 approx_pi =
      (4 * step / 2) * std::accumulate(sums.begin(), sums.end(), 0);
  char approx_pi_buffer[256] = {0};
  int err = quadmath_snprintf(approx_pi_buffer, 256, "%.15Qf", approx_pi);
  if (err < 0) {
    std::cout << "error: " << err << std::endl;
  }

  double PI = 3.141592653589793238462643383279502884197169399375105820974944592;


  std::cout << std::setw(wid) << "pi: " << approx_pi_buffer << std::endl;
//  std::cout << std::setw(wid) << "pi: " << std::fixed <<
//  std::setprecision(digits) << approx_pi_buffer << std::endl;
  std::cout << std::setw(wid) << "real pi: " << std::fixed <<
  std::setprecision(digits) << PI << std::endl;
//  std::cout << std::setw(wid) << "ratio: " << std::fixed <<
//  std::setprecision(digits) << PI / approx_pi << std::endl;
  std::cout << std::setw(wid) << "time taken: " << std::setw(digits + 2) <<
  time <<
  std::endl;


  return 0;
}
