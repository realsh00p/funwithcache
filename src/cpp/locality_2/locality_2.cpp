#include "locality_2.hpp"

#include <iostream>
#include <memory>
#include <numeric>

#include "Matrix.hpp"
#include "Primitive.hpp"
#include "Realtime.hpp"
#include "Result.hpp"
#include "Timer.hpp"
#include "Warmup.hpp"

namespace funwithprofiler {
namespace locality_2 {

using primitive::u64;

static const std::size_t LENGTH = 10000;

static auto run_heap_random() -> Result {
  Result ret;
  int sum = 0, elapsed_cycles = 0, elapsed_us = 0;

  std::vector<std::shared_ptr<u64>> backing;
  for (int i = 0; i < LENGTH; ++i) {
    backing.push_back(std::make_shared<u64>(1));
  }

  std::vector<u64 *> cut;
  std::for_each(backing.begin(), backing.end(),
                [&](auto elem) { cut.push_back(elem.get()); });

  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  std::for_each(cut.begin(), cut.end(), [&sum](auto elem) { sum += *elem; });

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

  std::vector<u64> backing;
  backing.resize(LENGTH, 1);

  std::vector<u64 *> cut;
  std::for_each(backing.begin(), backing.end(),
                [&](auto elem) { cut.push_back(&elem); });

  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  std::for_each(cut.begin(), cut.end(), [&sum](auto elem) { sum += *elem; });

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
  case Storage::HEAP_RANDOM:
    res = run_heap_random();
    break;
  case Storage::HEAP_CONTIGUOUS:
    res = run_heap_contiguous();
    break;
  default:
    throw;
  }
  return res;
}

} // namespace locality_2
} // namespace funwithprofiler
