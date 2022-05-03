#include "Warmup.hpp"

#include <memory>
#include <vector>

namespace funwithprofiler {
namespace warmup {

// this is not made to be fast
// it's made to be dump on purpose
// vector<shared<bool>> - yes this is dumb
auto SieveOfSundaramSum(std::uint64_t n) -> std::uint64_t {
  std::uint64_t sum = n > 2 ? 2 : 0;
  std::uint64_t nNew = (n - 1) / 2;

  std::vector<std::shared_ptr<bool>> marked;
  marked.resize(nNew + 1, std::make_shared<bool>(false));

  for (std::uint64_t i = 1; i <= nNew; i++)
    for (std::uint64_t j = i; (i + j + 2 * i * j) <= nNew; j++)
      *marked.at(i + j + 2 * i * j) = true;

  for (std::uint64_t i = 1; i <= nNew; i++)
    if (*marked.at(i) == false)
      sum += 2 * i + 1;

  return sum;
}

} // namespace warmup
} // namespace funwithprofiler
