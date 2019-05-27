#include "ConvexHull.hpp"

std::vector<size_t> LowerConvexHull(std::vector<Point2D > P)
 {
  // std::vector<Point2D> Q = P;
  const size_t n = P.size();
  size_t kk = 0, ii;
  std::vector<size_t> L(n);
  sort(P.begin(), P.end());

  if (n<=3) {
    double lastx = 0;
    for(size_t ii = 0; ii < n; ii++)
      if(ii == 0) {
	L[kk++] = P[ii].id();
	lastx = P[ii].x;
      } else {
	if(P[ii].x != lastx) {
	  L[kk++] = P[ii].id();
	}
      }
  } else {
    std::vector<Point2D> H(n);
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
    while(H.end()[-1].x == H.end()[-2].x) {
      L.pop_back();
      H.pop_back();
    }
  }

  // std::ofstream points((f+"_points.txt").c_str());
  // for(size_t ii = 0; ii < P.size(); ii++) {
  //   points << P[ii] << std::endl;
  // }
  // std::ofstream convex((f+"_convex.txt").c_str());
  // for(size_t ii = 0; ii < L.size(); ii++) {
  //   convex << Q[L[ii]] << std::endl;
  // }

  return L;
}
