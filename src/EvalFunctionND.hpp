#ifndef DIRECT_EVAL_FUNCTION_ND_HPP
#define DIRECT_EVAL_FUNCTION_ND_HPP

#include "typedefs.hpp"

double EvalFunctionND(functND f, const PointND& x, const PointND& LowerBound, const PointND& UpperBound, const void* data);

#endif
