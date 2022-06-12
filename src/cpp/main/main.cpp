#include "cache_miss.hpp"
#include "locality_1.hpp"

#include "Realtime.hpp"
#include "Warmup.hpp"

#include <fstream>
#include <iostream>
#include <numeric>

#include <boost/program_options.hpp>
#include <google/protobuf/text_format.h>

using namespace funwithprofiler;
namespace po = boost::program_options;

class Suite {
  enum {
    // clang-format off
    SUITE_UNDEFINED                 = 0,
    SUITE_LEN                       = 9,

    CACHE_MISS_HEAP_BREADTH_FIRST   = 1,
    CACHE_MISS_HEAP_DEPTH_FIRST     = 2,
    CACHE_MISS_STACK_BREADTH_FIRST  = 3,
    CACHE_MISS_STACK_DEPTH_FIRST    = 4,
    CACHE_MISS_STATIC_BREADTH_FIRST = 5,
    CACHE_MISS_STATIC_DEPTH_FIRST   = 6,
    LOCALITY_1_HEAP                 = 7,
    LOCALITY_1_STATIC               = 8,
    // clang-format on
  };

  std::array<int, SUITE_LEN - 1> suite;

public:
  Suite() {
    std::iota(suite.begin(), suite.end(), 1);
    std::random_shuffle(suite.begin(), suite.end());
  }

  auto run(const int sundaram, Tests *const tests) {
    for (auto &&s : suite) {
      auto test{tests->add_test()};
      warmup::sieve_of_sundaram(sundaram);
      switch (s) {
      case CACHE_MISS_HEAP_BREADTH_FIRST:
        test->mutable_cache_miss()->set_storage(Storage::HEAP);
        test->mutable_cache_miss()->set_traversal(Traversal::BREADTH_FIRST);
        test->mutable_cache_miss()->mutable_result()->CopyFrom(
            cache_miss::run(Storage::HEAP, Traversal::BREADTH_FIRST));
        break;
      case CACHE_MISS_HEAP_DEPTH_FIRST:
        test->mutable_cache_miss()->set_storage(Storage::HEAP);
        test->mutable_cache_miss()->set_traversal(Traversal::DEPTH_FIRST);
        test->mutable_cache_miss()->mutable_result()->CopyFrom(
            cache_miss::run(Storage::HEAP, Traversal::DEPTH_FIRST));
        break;
      case CACHE_MISS_STACK_BREADTH_FIRST:
        test->mutable_cache_miss()->set_storage(Storage::STACK);
        test->mutable_cache_miss()->set_traversal(Traversal::BREADTH_FIRST);
        test->mutable_cache_miss()->mutable_result()->CopyFrom(
            cache_miss::run(Storage::STACK, Traversal::BREADTH_FIRST));
        break;
      case CACHE_MISS_STACK_DEPTH_FIRST:
        test->mutable_cache_miss()->set_storage(Storage::STACK);
        test->mutable_cache_miss()->set_traversal(Traversal::DEPTH_FIRST);
        test->mutable_cache_miss()->mutable_result()->CopyFrom(
            cache_miss::run(Storage::STACK, Traversal::DEPTH_FIRST));
        break;
      case CACHE_MISS_STATIC_BREADTH_FIRST:
        test->mutable_cache_miss()->set_storage(Storage::STATIC);
        test->mutable_cache_miss()->set_traversal(Traversal::BREADTH_FIRST);
        test->mutable_cache_miss()->mutable_result()->CopyFrom(
            cache_miss::run(Storage::STATIC, Traversal::BREADTH_FIRST));
        break;
      case CACHE_MISS_STATIC_DEPTH_FIRST:
        test->mutable_cache_miss()->set_storage(Storage::STATIC);
        test->mutable_cache_miss()->set_traversal(Traversal::DEPTH_FIRST);
        test->mutable_cache_miss()->mutable_result()->CopyFrom(
            cache_miss::run(Storage::STATIC, Traversal::DEPTH_FIRST));
        break;
      case LOCALITY_1_HEAP:
        test->mutable_locality1()->set_storage(Storage::HEAP);
        test->mutable_locality1()->mutable_result()->CopyFrom(
            locality_1::run(Storage::HEAP));
        break;
      case LOCALITY_1_STATIC:
        test->mutable_locality1()->set_storage(Storage::STATIC);
        test->mutable_locality1()->mutable_result()->CopyFrom(
            locality_1::run(Storage::STATIC));
        break;
      }
    }
    return tests;
  }
};

int main(int argc, char *argv[]) {
  realtime::Realtime<SCHED_FIFO> realtime;

  po::options_description desc("options");
  // clang-format off
  desc.add_options()
    ("iterations", po::value<int>(), "number of iterations to run")
    ("sundaram", po::value<int>(), "size of warmup prime calculation");
  // clang-format on

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (!vm.count("iterations") || !vm.count("sundaram")) {
    std::cerr << desc << std::endl;
    return 1;
  }

  std::vector<Suite> iterations;
  iterations.resize(vm["iterations"].as<int>());

  const auto sundaram(vm["sundaram"].as<int>());
  Tests tests;
  for (auto &&i : iterations) {
    i.run(sundaram, &tests);
  }

  std::string output;
  google::protobuf::TextFormat::PrintToString(tests, &output);
  std::ofstream ofs{"output.proto"};
  ofs << output;
}
