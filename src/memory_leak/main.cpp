#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include "Args.hpp"
#include "Matrix.hpp"
#include "Primitive.hpp"

using namespace funwithprofiler;

using Matrix = matrix::Matrix<primitive::u64, 1000, 1000>;

[[gnu::noinline]] auto do_leak_mem() {
  auto tot{0};
  for (auto i = 0; i < 10; ++i) {
    auto m{new Matrix()};
    tot += m->depth_first();
  }
  return tot;
}

[[gnu::noinline]] auto dont_leak_mem() {
  auto tot{0};
  for (auto i = 0; i < 10; ++i) {
    auto m{std::make_unique<Matrix>()};
    tot += m->depth_first();
  }
  return tot;
}

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description desc("Options");
  // clang-format off
  desc.add_options()
    ("leak", po::value<YesOrNo>(), "[yes | no]");
  // clang-format on

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  auto leak{vm["leak"].as<YesOrNo>()};

  switch (leak) {
  case YesOrNo::YES:
    std::cout << "[ leak - " << leak << " ] " << do_leak_mem() << std::endl;
    break;
  case YesOrNo::NO:
    std::cout << "[ leak - " << leak << " ] " << dont_leak_mem() << std::endl;
    break;
  }

  return 0;
}
