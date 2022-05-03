#include "Args.hpp"

namespace funwithprofiler {

std::istream &operator>>(std::istream &in, YesOrNo &value) {
  std::string token;
  in >> token;
  if (token == "yes")
    value = YesOrNo::YES;
  else if (token == "no")
    value = YesOrNo::NO;
  else
    in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream &operator<<(std::ostream &os, const YesOrNo &value) {
  switch (value) {
  case YesOrNo::YES:
    return os << "yes";
  case YesOrNo::NO:
    return os << "no ";
  default:
    throw;
  }
}

std::istream &operator>>(std::istream &in, Storage &value) {
  std::string token;
  in >> token;
  if (token == "stack")
    value = Storage::STACK;
  else if (token == "static")
    value = Storage::STATIC;
  else if (token == "heap")
    value = Storage::HEAP;
  else
    in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream &operator<<(std::ostream &os, const Storage &value) {
  switch (value) {
  case Storage::STACK:
    return os << " stack";
  case Storage::STATIC:
    return os << "static";
  case Storage::HEAP:
    return os << "  heap";
  default:
    throw;
  }
}

std::istream &operator>>(std::istream &in, Traversal &value) {
  std::string token;
  in >> token;
  if (token == "depth-first")
    value = Traversal::BREADTH_FIRST;
  else if (token == "breadth-first")
    value = Traversal::DEPTH_FIRST;
  else
    in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream &operator<<(std::ostream &os, const Traversal &value) {
  switch (value) {
  case Traversal::BREADTH_FIRST:
    return os << "breadth-first";
  case Traversal::DEPTH_FIRST:
    return os << "depth-first  ";
  default:
    throw;
  }
}

} // namespace funwithprofiler
