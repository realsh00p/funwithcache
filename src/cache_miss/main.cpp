#include <ctime>
#include <iostream>
#include <istream>
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

using Matrix = matrix::Matrix<primitive::u64, 1000, 1010>;
using Result = result::Result<Matrix>;

[[gnu::noinline]] auto run(Matrix *p, const Traversal &traversal) -> Result {
  Result ret;
  TimerPosix timer_posix;
  TimerTSC timer_tsc;

  p->cache_flush();
  switch (traversal) {
  case Traversal::BREADTH_FIRST:
    ret.sum = p->breadth_first();
    break;
  case Traversal::DEPTH_FIRST:
    ret.sum = p->depth_first();
    break;
  default:
    throw;
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
  // clang-format off
  desc.add_options()
    ("storage", po::value<Storage>(), "[stack | static | heap]")
    ("traversal", po::value<Traversal>(), "[breadth-first | depth-first]");
  // clang-format on

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (!vm.count("storage") || !vm.count("traversal")) {
    std::cerr << desc << std::endl;
    return 1;
  }

  auto storage{vm["storage"].as<Storage>()};
  auto traversal{vm["traversal"].as<Traversal>()};
  Result res;

  // clang-format off
  switch (storage) {
    case Storage::STACK: {
      Matrix matrix;
      res = run(&matrix, traversal);
      break;
    }
    case Storage::STATIC: {
      static Matrix matrix;
      res = run(&matrix, traversal);
      break;
    }
    case Storage::HEAP: {
      auto matrix{std::make_unique<Matrix>()};
      res = run(matrix.get(), traversal);
      break;
    }
  }
  // clang-format on

  std::cout << "(cache_miss)\t[" << storage << " - " << traversal << "]\t"
            << res << std::endl;

  return 0;
}
