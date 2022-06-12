#include "locality_2.hpp"

#include <iostream>
#include <memory>

#include "Matrix.hpp"
#include "Primitive.hpp"
#include "Realtime.hpp"
#include "Result.hpp"
#include "Timer.hpp"
#include "Warmup.hpp"

namespace funwithprofiler {
namespace locality_2 {

using Matrix = matrix::Matrix<primitive::u64, 100, 1000>;

static auto run_heap_random() -> Result {
  Result ret;
  int sum = 0, elapsed_cycles = 0, elapsed_us = 0;

  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  elapsed_cycles = timer_tsc.elapsed_cycles();
  elapsed_us = timer_posix.elapsed_us();

  ret.set_sum(sum);
  ret.set_elapsed_cycles(elapsed_cycles);
  ret.set_elapsed_us(elapsed_us);
  return ret;
}

static auto run_heap_contiguous() -> Result {
  Result ret;
  int sum = 0, elapsed_cycles = 0, elapsed_us = 0;

  TimerPosix timer_posix;
  TimerTSC timer_tsc;

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
  default:
    throw;
  }
  return res;
}

} // namespace locality_2
} // namespace funwithprofiler
