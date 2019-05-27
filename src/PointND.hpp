#ifndef DIRECT_POINTND_HPP
#define DIRECT_POINTND_HPP

#include <vector>
#include <iostream>

class PointND {
private:
  size_t d;
  std::vector<double> x;
public:
  PointND(size_t d_) {
    d = d_;
    x = std::vector<double>(d);
  }
  PointND(size_t d_, double val) {
    d = d_;
    x = std::vector<double>(d);
    for(size_t ii = 0; ii < d; ii++) {
      x[ii] = val;
    }
  }
  PointND() {}

  size_t Dimension(void) const {
    return d;
  }

  double operator[](size_t ii) const {
    return x[ii];
  }

  double& operator[](size_t ii) {
    return x[ii];
  }

  friend std::ostream& operator<<(std::ostream& os, const PointND& P)
  {
    for(size_t ii = 0; ii < P.d; ii++) {
      os << P.x[ii] << std::endl;
    }
    return os;
  }

};

#endif
