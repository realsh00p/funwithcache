#include <iostream>
#include <memory>

#include <x86intrin.h>

#include "Matrix.hpp"
#include "Primitive.hpp"

using namespace funwithcache;

using Matrix = matrix::Matrix<primitive::u64, 1000, 1000>;
int main(void) {

  auto m{std::make_shared<Matrix>()};
  std::uint32_t tsc;
  std::uint64_t t1, t2;

  Matrix::value_type sum{0};

  m->cache_flush();
  t1 = __rdtscp(&tsc);
  sum = m->depth_first();
  t2 = __rdtscp(&tsc) - t1;

  std::cout << "[heap] depth_first elapsed: " << t2 << " (tot: " << sum << ")"
            << std::endl;

  m->cache_flush();
  t1 = __rdtscp(&tsc);
  sum = m->breadth_first();++
  t2 = __rdtscp(&tsc) - t1;

  std::cout << "[heap] breadth_first elapsed: " << t2 << " (tot: " << sum << ")"
            << std::endl;

  auto n{Matrix{}};

  n.cache_flush();
  t1 = __rdtscp(&tsc);
  sum = n.depth_first();
  t2 = __rdtscp(&tsc) - t1;

  std::cout << "[stack] depth_first elapsed: " << t2 << " (tot: " << sum << ")"
            << std::endl;

  n.cache_flush();
  t1 = __rdtscp(&tsc);
  sum = n.depth_first();
  t2 = __rdtscp(&tsc) - t1;

  std::cout << "[stack] breadth_first elapsed: " << t2 << " (tot: " << sum
            << ")" << std::endl;

  return 0;
}
