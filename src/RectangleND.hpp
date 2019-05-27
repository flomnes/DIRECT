#ifndef DIRECT_RECTANGLE_ND_HPP
#define DIRECT_RECTANGLE_ND_HPP

#include "PointND.hpp"
#include "typedefs.hpp"
#include "EvalFunctionND.hpp"
#include <cmath>


class RectangleND {
  // c : center of rectangle
  // l : half-length of sides
  // fc : value of f evaluated at the center
private:
  PointND c, l;
  size_t d;
  double fc;

public:
  RectangleND() {
  }

  RectangleND(size_t d_) {
    d = d_;
    c = PointND(d);
    l = PointND(d);
  }
  RectangleND(PointND c_, PointND l_, size_t d_) {
    c = c_;
    l = l_;
    d = d_;
  }

  // Create new rectangle from old one using pre-computed value at center
  // TopBottom = 0 or 1
  RectangleND(const RectangleND& R, double ValueAtCenter, size_t AlongDimension, int TopBottom) {
    d = R.d;
    fc = ValueAtCenter;
    c = PointND(d);
    l = PointND(d);
    const int dj = 2*TopBottom-1;
    for(size_t ii = 0; ii < d; ii++) {
      if(ii == AlongDimension) {
	const double delta = R.l[ii]/3;
	c[ii] = R.c[ii] + 2*dj*delta;
	l[ii] = R.l[ii] / 3;
      } else {
	c[ii] = R.c[ii];
	l[ii] = R.l[ii];
      }
    }
  }

  // TODO : store value in class variable to avoid recomputations
  double Distance(void) const {
    double sum = 0;
    for(size_t ii = 0; ii < d; ii++) {
      sum += l[ii]*l[ii];
    }
    return std::sqrt(sum);
  }

  double LongestHalfSide(void) const {
    double r = l[0];
    for(size_t ii = 1; ii < d; ii++) {
      if(r < l[ii]) r = l[ii];
    }
    return r;
  }

  std::vector<size_t> LongestHalfSideDimensions(double& delta) const {
    double m = l[0];
    for(size_t ii = 1; ii < d; ii++) {
      if(m < l[ii]) {
	m = l[ii];
      }
    }
    std::vector<size_t> Dims(d);
    size_t kk = 0;
    for(size_t ii = 0; ii < d; ii++) {
      if(l[ii] == m) Dims[kk++] = ii;
    }
    Dims.resize(kk);
    delta = m/3;
    return Dims;
  }

  double ValueAtCenter(void) const {
    return fc;
  }

  double EvalAtCenter(functND f, const PointND& LowerBound, const PointND& UpperBound, const void* data) {
    fc = EvalFunctionND(f, c, LowerBound, UpperBound, data);
    return fc;
  }

  friend void Flatten(RectangleND& R, size_t dim) {
    R.l[dim] /= 3;
  }


  PointND Center(void) const {
    return c;
  }


  double Center(size_t ii) const {
    return c[ii];
  }


  double& Center(size_t ii) {
    return c[ii];
  }

  double HalfLength(size_t ii) const {
    return l[ii];
  }

  double& HalfLength(size_t ii) {
    return l[ii];
  }

};
#endif
