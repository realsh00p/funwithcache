#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

#include <emmintrin.h>

namespace funwithprofiler {
namespace matrix {

template <typename T, std::size_t Height, std::size_t Width>
class __attribute__((packed)) Matrix
    : public std::array<std::array<T, Height>, Width> {
public:
  static constexpr auto height_value = Height;
  static constexpr auto width_value = Width;
  using value_type = T;

  Matrix() {
    for (std::size_t i = 0; i < width_value; ++i) {
      for (std::size_t j = 0; j < height_value; ++j) {
        this->data()[i][j] = 1;
      }
    }
  }

  auto depth_first() -> value_type {
    value_type tot{0};
    for (std::size_t i = 0; i < width_value; ++i) {
      for (std::size_t j = 0; j < height_value; ++j) {
        tot += this->data()[i][j];
      }
    }
    return tot;
  }

  auto breadth_first() -> value_type {
    value_type tot{0};
    for (std::size_t i = 0; i < height_value; ++i) {
      for (std::size_t j = 0; j < width_value; ++j) {
        tot += this->data()[j][i];
      }
    }
    return tot;
  }

  void cache_flush() {
    _mm_clflush(this->data());
    _mm_clflush(this);
  }
};

} // namespace matrix
} // namespace funwithprofiler
