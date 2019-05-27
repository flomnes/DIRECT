#include <cstddef>
#include "PreSplitContainer.hpp"

double PreSplit::min(void) const {
  if(Values[0] < Values[1])
    return Values[0];
  else
    return Values[1];
}

bool compare_function(const PreSplit& x,const PreSplit& y)
{
  return x.min() < y.min();
}

void CompareEvals(std::vector<PreSplit>& evals)
{
  std::sort(evals.begin(), evals.end(), compare_function);
}
