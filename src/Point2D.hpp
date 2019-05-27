#ifndef DIRECT_POINT2D_HPP
#define DIRECT_POINT2D_HPP

#include <iostream>
#include <vector>

class Point2D {
private:
  double x, y;
  size_t TempId;
public:
  Point2D(void) {
  }
  Point2D(double x_, double y_) {
    x = x_;
    y = y_;
  }

  Point2D(double x_, double y_, size_t TempId_) {
    x = x_;
    y = y_;
    TempId = TempId_;
  }


  size_t id(void) {
    return TempId;
  }

  bool operator <(const Point2D &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }

  friend std::ostream& operator<<(std::ostream& os, const Point2D& P)
  {
    return os << P.x << " " << P.y;
  }

  friend double cross(const Point2D &O, const Point2D &A, const Point2D &B)
  {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
  }

  friend double slope(const Point2D& A, const Point2D& B)
  {
    return (B.y - A.y) / (B.x - A.x);
  }
  friend std::vector<size_t> LowerConvexHull(std::vector<Point2D > P);
};

#endif
