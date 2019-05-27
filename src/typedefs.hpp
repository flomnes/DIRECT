#ifndef DIRECT_TYPEDEFS_HPP
#define DIRECT_TYPEDEFS_HPP
#include <utility>
#include "PointND.hpp"

typedef double (*functND)(const PointND&, const void* data);

//TODO remove
template<typename T>
void display(std::ostream& os, const std::vector<T>& v, char delim='\n') {
  const size_t n = v.size();
  if(n>0) {
  for(size_t ii = 0; ii < n; ii++) {
    os << v[ii] << delim;
  }
  os << std::endl;
  }
}

#ifdef DEBUG
static size_t idx_cvx = 0;
#endif

#endif
