#pragma once

#include <ctime>
#include <x86intrin.h>

#include "Primitive.hpp"

namespace funwithprofiler {

class TimerPosix {
public:
  TimerPosix() { reset(); }

  void reset() { start(); }
  void start() { clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time_start); }

  auto elapsed_us() -> primitive::u64 {
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time_end);
    return diff_us(time_end, time_start);
  }

private:
  struct timespec time_start, time_end;

  static auto diff_us(std::timespec time_end, std::timespec time_start)
      -> primitive::u64 {
    return (time_end.tv_sec - time_start.tv_sec) * 1e6f +
           (time_end.tv_nsec - time_start.tv_nsec) / 1e3f;
  }
};

class TimerTSC {
public:
  TimerTSC() { reset(); }

  void reset() { start(); }

  void start() { time_start = __rdtscp(&mem); }

  auto elapsed_cycles() -> primitive::u64 {
    return __rdtscp(&mem) - time_start;
  }

private:
  std::uint32_t mem;
  std::uint64_t time_start;
};

} // namespace funwithprofiler
