#include "ConvexHull.hpp"

std::vector<size_t> LowerConvexHull(std::vector<Point2D > P)
 {
  const size_t n = P.size();
  size_t kk = 0, ii;
  std::vector<size_t> L(n);
  std::vector<Point2D> H(n);
  sort(P.begin(), P.end());
    // Build lower hull
    for (ii = 0; ii < n; ii++) {
      while (kk >= 2 && cross(H[kk-2], H[kk-1], P[ii]) <= 0) kk--;
      H[kk] = P[ii];
      L[kk] = P[ii].id();
      kk++;
    }
    L.resize(kk);
    H.resize(kk);
  // Remove points with the same x coordinate on the right part of the convex hull
    if(H.size() > 1) {
      while(H.end()[-1].x == H.end()[-2].x) {
	L.pop_back();
	H.pop_back();
      }
    }
  return L;
}
