#include <iostream>
#include "typedefs.hpp"
#include "PointMixed.hpp"

PointMixed CreatePointMixed(const PointND<double>& Pf, const PointND<int>& Pi)
{
  return std::make_pair(Pf, Pi);
}

std::ostream& operator<<(std::ostream& os, const PointMixed& P) {
  return os << P.first << " " << P.second;
}
