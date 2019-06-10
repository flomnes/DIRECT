#ifndef DIRECT_RECTANGLE_FLOAT_HPP
#define DIRECT_RECTANGLE_FLOAT_HPP

#include <cassert>

class RectangleFloat {
private:
  PointND<double> center;
  std::vector<unsigned int> divisions;
public:
  RectangleFloat() {
  }

  RectangleFloat(size_t dim) {
    center = PointND<double>(dim);
  }

  RectangleFloat(const PointND<double>& LowerBound, const PointND<double>& UpperBound) {
    assert(LowerBound.Dimension() == UpperBound.Dimension());
    const size_t d = LowerBound.Dimension();
    center = PointND<double>(d);
    divisions = std::vector<unsigned int>(d, 0);
    for(size_t ii = 0; ii < d; ii++) {
      center[ii] = (LowerBound[ii]+UpperBound[ii])/2;
    }
  }

  size_t Dimension() const {
    return center.Dimension();
  }

  PointND<> Center() const {
    return center;
  }

  PointND<>& Center(){
    return center;
  }

  double Center(size_t dir) const {
    return center[dir];
  }

  double& Center(size_t dir){
    return center[dir];
  }

  unsigned int NumberDivisions(size_t dim) const {
    return divisions[dim];
  }

  unsigned int& NumberDivisions(size_t dim) {
    return divisions[dim];
  }
};


#endif
