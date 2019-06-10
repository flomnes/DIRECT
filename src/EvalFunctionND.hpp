#ifndef DIRECT_EVAL_FUNCTION_ND_HPP
#define DIRECT_EVAL_FUNCTION_ND_HPP

#include "typedefs.hpp"

double EvalFunctionND(functND f, const PointMixed& x, const PointMixed& LowerBound, const PointMixed& UpperBound, const void* data);

#endif
