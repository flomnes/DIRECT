#ifndef DIRECT_POINTND_HPP
#define DIRECT_POINTND_HPP

#include <vector>
#include <iostream>

template<typename T = double>
class PointND {
private:
  std::vector<T> x;
  char delimiter = ' ';
public:
  PointND(size_t d_) {
    x = std::vector<T>(d_);
  }
  PointND(size_t d_, T val) {
    x = std::vector<T>(d_, val);
  }

  PointND() {
    x = std::vector<T>(0);
  }

  PointND(PointND P1, PointND P2) {
    x.reserve(P1.x.size() + P1.x.size());
    x.insert(x.end(), P1.x.begin(), P1.x.end());
    x.insert(x.end(), P2.x.begin(), P2.x.end());
  }

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
      os << P.x[ii] << P.delimiter;
    }
    return os;
  }
};

#endif
