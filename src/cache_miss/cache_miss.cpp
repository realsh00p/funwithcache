#include "cache_miss.hpp"

#include <iostream>
#include <memory>

#include "Args.hpp"
#include "Matrix.hpp"
#include "Primitive.hpp"
#include "Realtime.hpp"
#include "Result.hpp"
#include "Timer.hpp"
#include "Warmup.hpp"

namespace funwithprofiler {
namespace cache_miss {

using Matrix = matrix::Matrix<primitive::u64, 100, 100>;

static auto run_cache_miss(Matrix *p, const Traversal &traversal) -> Result {
  Result ret;
  int sum = 0, elapsed_cycles = 0, elapsed_us = 0;

  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  p->cache_flush();
  switch (traversal) {
  case Traversal::BREADTH_FIRST:
    sum = p->breadth_first();
    break;
  case Traversal::DEPTH_FIRST:
    sum = p->depth_first();
    break;
  default:
    throw;
  }

  elapsed_cycles = timer_tsc.elapsed_cycles();
  elapsed_us = timer_posix.elapsed_us();

  ret.set_sum(sum);
  ret.set_elapsed_cycles(elapsed_cycles);
  ret.set_elapsed_us(elapsed_us);
  return ret;
}

auto run(const Storage &storage, const Traversal &traversal) -> Result {
  Result res;
  // clang-format off
  switch (storage) {
    case Storage::STACK: {
      Matrix matrix;
      res = run_cache_miss(&matrix, traversal);
      break;
    }
    case Storage::STATIC: {
      static Matrix matrix;
      res = run_cache_miss(&matrix, traversal);
      break;
    }
    case Storage::HEAP: {
      auto matrix{std::make_unique<Matrix>()};
      res = run_cache_miss(matrix.get(), traversal);
      break;
    }
  }
  // clang-format on

  return res;
}

} // namespace cache_miss
} // namespace funwithprofiler
