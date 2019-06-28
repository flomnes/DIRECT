#ifndef DIRECT_POINT_MIXED_HPP
#define DIRECT_POINT_MIXED_HPP

#include <iostream>
#include <utility>
#include "typedefs.hpp"

PointMixed CreatePointMixed(const PointND<double>& Pf, const PointND<int>& Pi = PointND<int>());

std::ostream& operator<<(std::ostream& os, const PointMixed& P);
#endif
