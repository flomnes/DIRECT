#ifndef DIRECT_CONVEXHULL_HPP
#define DIRECT_CONVEXHULL_HPP
#include <iostream>
#include <fstream>
#include <string>

#include <map>
#include <algorithm>
#include "Point2D.hpp"

std::vector<size_t> LowerConvexHull(std::map<size_t, Point2D > P);


#endif
