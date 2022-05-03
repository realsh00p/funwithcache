#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include "Args.hpp"
#include "Matrix.hpp"
#include "Primitive.hpp"
#include "Realtime.hpp"
#include "Result.hpp"
#include "Timer.hpp"
#include "Warmup.hpp"

using namespace funwithprofiler;

using Matrix = matrix::Matrix<primitive::u64, 100, 100>;
using Result = result::Result<Matrix>;

[[gnu::noinline]] auto run_static() -> Result {
  static std::array<Matrix, 100> matrices{};

  Result ret;
  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  for (auto &m : matrices) {
    ret.sum += m.depth_first();
  }

  ret.elapsed_cycles = timer_tsc.elapsed_cycles();
  ret.elapsed_us = timer_posix.elapsed_us();

  return ret;
}

[[gnu::noinline]] auto run_heap() -> Result {
  std::array<std::unique_ptr<Matrix>, 100> matrices;
  for (auto &m : matrices) {
    void *p = malloc(sizeof(Matrix) / 2);
    m = std::make_unique<Matrix>();
    free(p);
  }

  Result ret;
  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  for (auto &m : matrices) {
    ret.sum += m->depth_first();
  }

  ret.elapsed_cycles = timer_tsc.elapsed_cycles();
  ret.elapsed_us = timer_posix.elapsed_us();

  return ret;
}

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  Realtime<SCHED_FIFO> realtime;
  warmup::SieveOfSundaramSum(1e7);

  po::options_description desc("options");
  desc.add_options()("storage", po::value<Storage>(),
                     "[stack | static | heap]");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (!vm.count("storage")) {
    std::cerr << desc << std::endl;
    return 1;
  }

  auto storage{vm["storage"].as<Storage>()};
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

  std::cout << "(locality)\t[" << storage << " - depth-first  ]\t" << res
            << std::endl;

  return 0;
}
