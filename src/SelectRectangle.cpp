#include "DIRECT.hpp"
#include <limits>

#ifdef DEBUG
static int idx_cvx = 0;
#endif

std::vector<size_t> DIRECT::SelectRectanglesFromSlopes(const std::vector<size_t>& LCHIndices, const std::vector<Point2D>& DistanceValuesAtCenters)
{
  std::vector<size_t> SelectedRectanglesIds;
  const size_t m = LCHIndices.size();
  if(m>0) {
    double s = 0, smin = 0;
    size_t kk = 0;
    const Point2D Origin(0, fmin-epsilon);
    std::vector<size_t> RectangleIds(m);
    for(size_t ii = 1; ii < m; ii++) {
      s = slope(DistanceValuesAtCenters.at(LCHIndices[ii-1]), DistanceValuesAtCenters.at(LCHIndices[ii]));
      smin = slope(DistanceValuesAtCenters.at(LCHIndices[ii-1]), Origin);
      if(s>=0 && s>=smin) {
	RectangleIds[kk++] = LCHIndices[ii-1];
      }
    }
    if(s>=0 && s>=smin) {
      RectangleIds[kk++] = LCHIndices[m-1];
    }
    if(kk>0) {
      RectangleIds.resize(kk);
    } else {
      RectangleIds = LCHIndices;
    }
#ifdef DEBUG
    std::ofstream cvx("resu/df_cvx"+std::to_string(idx_cvx)+".txt");
    for(size_t ii = 0; ii < RectangleIds.size(); ii++) {
      cvx << RectangleList[RectangleIds[ii]].Distance() << " " << RectangleList[RectangleIds[ii]].ValueAtCenter()  << std::endl;
    }
    std::ofstream pts("resu/df_pts"+std::to_string(idx_cvx)+".txt");
    for(size_t ii = 0; ii < RectangleList.size(); ii++) {
      pts << RectangleList[ii].Distance() << " " << RectangleList[ii].ValueAtCenter()  << std::endl;
    }
#endif
    return RectangleIds;
  } else {
    return LCHIndices;
  }
}

std::vector<size_t> DIRECT::PotentiallyOptimalRectangles(void)
{
  // Form the lower-right convex hull in the (f(c), d) plane
  const size_t n = RectangleList.size();
  // TODO : remove special case, move to LowerConvexHull
  if(n == 1) {
    std::vector<size_t> r(1);
    r[0] = 0;
    return r;
  }
  // Construct the list (f(c_j), d_j)
  std::vector<Point2D> DistanceValueAtCenters(n);

  for(size_t id = 0; id < n; id++) {
    if(RectangleList[id].IsDivisible())
      DistanceValueAtCenters[id] = Point2D(RectangleList[id].Distance(), RectangleList[id].ValueAtCenter(), id);
    else
      DistanceValueAtCenters[id] = Point2D(RectangleList[id].Distance(), std::numeric_limits<double>::max(), id);
  }

  // Compute the lower-right convex hull / DistanceValueAtCenters gets sorted
  std::vector<size_t> LCHIndices = LowerConvexHull(DistanceValueAtCenters);
  // Check the conditions slopes of the line segments
  std::vector<size_t> CondIndices = SelectRectanglesFromSlopes(LCHIndices, DistanceValueAtCenters);
#ifdef DEBUG
  std::ofstream pts("resu/pts"+std::to_string(idx_cvx)+".txt");
  std::ofstream cvx("resu/cvx"+std::to_string(idx_cvx)+".txt");
  idx_cvx++;
  for(size_t ii = 0; ii < CondIndices.size(); ii++) {
    cvx << RectangleList[CondIndices[ii]].Center(LowerBound, UpperBound) << std::endl;

  }

  for(size_t ii = 0; ii < RectangleList.size(); ii++) {
    pts << RectangleList[ii].Center(LowerBound, UpperBound) << std::endl;
  }
#endif

  return CondIndices;
}
