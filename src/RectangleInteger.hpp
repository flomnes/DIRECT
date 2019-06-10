#ifndef DIRECT_RECTANGLE_INTEGER_HPP
#define DIRECT_RECTANGLE_INTEGER_HPP

#include <vector>
#include <utility>
#include <cassert>
#include "PointND.hpp"


class RectangleInteger {
private:
  PointND<std::pair<int, int> > range;
  std::vector<unsigned int> divisions;
public:
  size_t Dimension() const {
    return range.Dimension();
  }

  RectangleInteger() {}

  RectangleInteger(const PointND<int>& LowerBound, const PointND<int>& UpperBound) {
    assert(LowerBound.Dimension() == UpperBound.Dimension());
    const size_t d = LowerBound.Dimension();
    range = PointND<std::pair<int,int> >(d);
    for(size_t ii = 0; ii < d; ii++) {
      range[ii] = std::make_pair(LowerBound[ii], UpperBound[ii]);
    }
    divisions = std::vector<unsigned int>(d, 0);
  }

  int ComputeDelta(size_t dir) const {
    return (range[dir].second - range[dir].first)/3;
  }

  PointND<int> Center() const {
    const size_t dim = Dimension();
    PointND<int> c(dim);
    for(size_t ii = 0; ii < dim; ii++) {
      c[ii] = (range[ii].first + range[ii].second) / 2;
    }
    return c;
  }

  unsigned int NumberDivisions(size_t dim) const {
    return divisions[dim];
  }

  unsigned int& NumberDivisions(size_t dim) {
    return divisions[dim];
  }

  bool IsDirectionAdmissible(size_t dim) const {
    return (range[dim].second - range[dim].first) > 1;
  }

  int& operator()(size_t dim, char jj) {
    if(jj==0) {
      return range[dim].first;
    }
    if(jj==1) {
      return range[dim].second;
    }
    return range[dim].first;
  }
};


#endif
