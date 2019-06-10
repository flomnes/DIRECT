#include "EvalFunctionND.hpp"

double EvalFunctionND(functND f, const PointMixed& x, const PointMixed& LowerBound, const PointMixed& UpperBound, const void* data)
 {
   const size_t df = x.first.Dimension();
   PointMixed xis = std::make_pair(PointND<>(df), x.second);
   for(size_t ii = 0; ii < df; ii++) {
     xis.first[ii] = x.first[ii] * (UpperBound.first[ii] - LowerBound.first[ii]) + LowerBound.first[ii];
   }
   return f(xis, data);
 }
