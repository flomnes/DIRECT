#include <cmath>
#include <iostream>
#include "DIRECT.hpp"


inline double square(double x) {
  return x*x;
}

double Rosenbrock(const PointND& v, const void* data) {
  const int n = *(int*)(data);
  double r = 0;
  for(int ii = 0; ii < n-1; ii++) {
    r+=100*square(v[ii+1]-square(v[ii]))+square(v[ii]-1);
  }
  return r;
}

double Custom(const PointND& v, const void* data) {
  const int n = *(int*)(data);
    double r = 0;
    for(int ii = 0; ii < n; ii++) {
      double q = .4;
      r+=square(v[ii]-q);
    }
  return r;
}

double Rastigrin(const PointND& v, const void* data) {
  const int n = *(int*)(data);
  double r = 10*n;
  for(int ii = 0; ii < n; ii++) {
    r += square(v[ii])-10*cos(2*M_PI*v[ii]);
  }
  return r;
}

double Ackley(const PointND& v, const void* data) {
  const int n = *(int*)(data);
  double sum = 0, sumc = 0;
  for(int ii = 0; ii < n; ii++) {
    sum += square(v[ii]);
    sumc += cos(2*M_PI*v[ii]);
  }
  return -20*exp(-.2*sqrt(1./n*sum)) - exp(1./n*sumc) + 20 + exp(1);
}

double StyblinskiTang(const PointND& v, const void* data) {
  const int n = *(int*)(data);
  double sum = 0;
  for(int ii = 0; ii < n; ii++) {
    sum += (pow(v[ii],4)-16*pow(v[ii],2)+5*v[ii]);
  }
  return sum / (2*n);
}



int main(int argc, char** argv) {
  if(argc > 3) {
    const functND l[] = {Rosenbrock, Custom, Rastigrin, Ackley, StyblinskiTang};
    const int d = std::atoi(argv[2]);
    PointND LB(d,2.1);
    PointND UB(d,0);

    DIRECT MD(l[2], d, LB, UB, std::atoi(argv[1]), std::atof(argv[3]), (void*)&d);
    std::cout << MD.Optimize() << std::endl;
#ifdef DEBUG
    MD.Postpro();
#endif
    return 0;
  } else {
    std::cerr << "Not enough arguments" << std::endl;
    return 1;
  }
}
