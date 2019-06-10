#include <cmath>
#include <iostream>
#include "DIRECT.hpp"


inline double square(double x) {
  return x*x;
}

double Rosenbrock(const PointND<>& v, const void* data) {
  const int n = *(int*)(data);
  double r = 0;
  for(int ii = 0; ii < n-1; ii++) {
    r+=100*square(v[ii+1]-square(v[ii]))+square(v[ii]-1);
  }
  return r;
}

double Custom(const PointND<>& v, const void* data) {
  const int n = *(int*)(data);
    double r = 0;
    for(int ii = 0; ii < n; ii++) {
      double q = .4;
      r+=square(v[ii]-q);
    }
  return r;
}

double Rastigrin(const PointND<>& v, const void* data) {
  const int n = *(int*)(data);
  double r = 10*n;
  for(int ii = 0; ii < n; ii++) {
    r += square(v[ii])-10*cos(2*M_PI*v[ii]);
  }
  return r;
}

double Ackley(const PointND<>& v, const void* data) {
  const int n = *(int*)(data);
  double sum = 0, sumc = 0;
  for(int ii = 0; ii < n; ii++) {
    sum += square(v[ii]);
    sumc += cos(2*M_PI*v[ii]);
  }
  return -20*exp(-.2*sqrt(1./n*sum)) - exp(1./n*sumc) + 20 + exp(1);
}

double StyblinskiTang(const PointND<>& v, const void* data) {
  const int n = *(int*)(data);
  double sum = 0;
  for(int ii = 0; ii < n; ii++) {
    sum += (pow(v[ii],4)-16*pow(v[ii],2)+5*v[ii]);
  }
  return sum / (2*n);
}


double Mixed1(const PointMixed& x, const void* data) {
  const auto Pf = x.first;
  const auto Pi = x.second;
  double r = 0;
  for(unsigned int ii = 0; ii < Pf.Dimension(); ii++) {
    r += Pf[ii];
  }
  for(unsigned int ii = 0; ii < Pi.Dimension(); ii++) {
    r += Pi[ii];
  }
  return r;
}

double Mixed2(const PointMixed& x, const void* data) {
  const auto Pf = x.first;
  const auto Pi = x.second;
  return std::cos(Pf[0]) + Pi[0];
}


int main(int argc, char** argv) {
  const PointMixed LB = CreatePointMixed(PointND<double>(1, -M_PI), PointND<int>(1,-10));
  const PointMixed UB = CreatePointMixed(PointND<double>(1, M_PI), PointND<int>(1,10));
  const unsigned int MaxEvals = 100;
  DIRECT D(Mixed2, LB, UB, MaxEvals);
  std::cout << D.Optimize() << std::endl;
}
