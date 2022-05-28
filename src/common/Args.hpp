#pragma once

#include "output.pb.h"

#include <istream>
#include <ostream>
#include <string>

namespace funwithprofiler {

enum YesOrNo { YES, NO };

std::istream &operator>>(std::istream &in, YesOrNo &value);
std::ostream &operator<<(std::ostream &os, const YesOrNo &value);

std::istream &operator>>(std::istream &in, Storage &value);
std::ostream &operator<<(std::ostream &os, const Storage &value);

std::istream &operator>>(std::istream &in, Traversal &value);
std::ostream &operator<<(std::ostream &os, const Traversal &value);

} // namespace funwithprofiler
