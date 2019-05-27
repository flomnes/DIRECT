#ifndef DIRECT_PRE_SPLIT_CONTAINER_HPP
#define DIRECT_PRE_SPLIT_CONTAINER_HPP

#include <vector>
#include <algorithm>

class PreSplit {
private:
  double Values[2];
  std::size_t dim;
public:
  double min(void) const;
  void SetDimension(size_t d) {
    dim = d;
  }

  std::size_t GetDimension(void) const {
    return dim;
  }

  double& operator[](std::size_t index) {
    return Values[index];
  }
  double operator[](std::size_t index) const {
    return Values[index];
  }
};

bool compare_function(const PreSplit& x,const PreSplit& y);
void CompareEvals(std::vector<PreSplit>& evals);


#endif
