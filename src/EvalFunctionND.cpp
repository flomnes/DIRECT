#include "EvalFunctionND.hpp"

double EvalFunctionND(functND f, const PointND& x, const PointND& LowerBound, const PointND& UpperBound, const void* data)
 {
  const size_t d = x.Dimension();
  PointND xis(d);
  for(size_t ii = 0; ii < d; ii++) {
    xis[ii] = x[ii] * (UpperBound[ii] - LowerBound[ii]) + LowerBound[ii];
  }
  return f(xis, data);
}
