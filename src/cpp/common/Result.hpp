#pragma once

#include "output.pb.h"

#include <cstdint>
#include <ostream>

namespace funwithprofiler {
namespace result {

inline std::ostream &operator<<(std::ostream &os, const Result &res) {
  return os << "elapsed: " << res.elapsed_us() << " [μs]\t"
            << res.elapsed_cycles() << " [cycles] (sum: " << res.sum() << ")";
}

} // namespace result
} // namespace funwithprofiler
