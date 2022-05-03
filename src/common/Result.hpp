#pragma once

#include <cstdint>
#include <ostream>

namespace funwithprofiler {
namespace result {

template <typename T>
struct Result {
  typename T::value_type sum{0};
  std::uint64_t elapsed_us, elapsed_cycles;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Result<T> &res) {
  return os << "elapsed: " << res.elapsed_us << " [μs]\t" << res.elapsed_cycles
            << " [cycles] (sum: " << res.sum << ")";
}

} // namespace result
} // namespace funwithprofiler
