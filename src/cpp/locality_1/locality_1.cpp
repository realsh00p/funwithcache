#include "locality_1.hpp"

#include <iostream>
#include <memory>

#include "Matrix.hpp"
#include "Primitive.hpp"
#include "Realtime.hpp"
#include "Result.hpp"
#include "Timer.hpp"
#include "Warmup.hpp"

namespace funwithprofiler {
namespace locality_1 {

using Matrix = matrix::Matrix<primitive::u64, 100, 1000>;

static auto run_static() -> Result {
  static std::array<Matrix, 100> matrices{};
  Result ret;
  int sum = 0, elapsed_cycles = 0, elapsed_us = 0;

  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  for (auto &m : matrices) {
    sum += m.depth_first();
  }

  elapsed_cycles = timer_tsc.elapsed_cycles();
  elapsed_us = timer_posix.elapsed_us();

  ret.set_sum(sum);
  ret.set_elapsed_cycles(elapsed_cycles);
  ret.set_elapsed_us(elapsed_us);
  return ret;
}

static auto run_heap() -> Result {
  Result ret;
  int sum = 0, elapsed_cycles = 0, elapsed_us = 0;

  std::array<std::unique_ptr<Matrix>, 100> matrices;
  for (auto &m : matrices) {
    void *p = malloc(sizeof(Matrix) / 2);
    m = std::make_unique<Matrix>();
    free(p);
  }

  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  for (auto &m : matrices) {
    sum += m->depth_first();
  }

  elapsed_cycles = timer_tsc.elapsed_cycles();
  elapsed_us = timer_posix.elapsed_us();

  ret.set_sum(sum);
  ret.set_elapsed_cycles(elapsed_cycles);
  ret.set_elapsed_us(elapsed_us);
  return ret;
}

auto run(const Storage &storage) -> Result {
  Result res;
  switch (storage) {
  case Storage::HEAP:
    res = run_heap();
    break;
  case Storage::STATIC:
    res = run_static();
    break;
  default:
    throw;
  }
  return res;
}

} // namespace locality_1
} // namespace funwithprofiler
