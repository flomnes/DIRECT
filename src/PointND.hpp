#ifndef DIRECT_POINTND_HPP
#define DIRECT_POINTND_HPP

#include <vector>
#include <iostream>

template<typename T = double>
class PointND {
private:
  std::vector<T> x;
public:
  PointND(size_t d_) {
    x = std::vector<T>(d_);
  }
  PointND(size_t d_, T val) {
    x = std::vector<T>(d_, val);
  }
  PointND() {}

  size_t Dimension(void) const {
    return x.size();
  }

  T operator[](size_t ii) const {
    return x[ii];
  }

  T& operator[](size_t ii) {
    return x[ii];
  }

  friend std::ostream& operator<<(std::ostream& os, const PointND<T>& P)
  {
    for(size_t ii = 0; ii < P.Dimension(); ii++) {
      os << P.x[ii] << " ";
    }
    return os;
  }
};

#endif
