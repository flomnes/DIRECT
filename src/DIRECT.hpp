#ifndef DIRECT_HPP
#define DIRECT_HPP

#include <vector>
#ifdef DEBUG
#include <iostream>
#include <fstream>
#include <string>
#endif
#include "RectangleND.hpp"
#include "ConvexHull.hpp"
#include "Point2D.hpp"
#include "typedefs.hpp"
#include "PointMixed.hpp"


class DIRECT {
#ifdef DIRECT_TESTING
public:
#else
private:
#endif
  // List of rectangles built by DIRECT algorithm, in the hypercube [0,1]^d
  std::vector<RectangleND > RectangleList;
  // Bounds imposed on variables in the optimization problem
  PointMixed LowerBound, UpperBound;
  // Minimum value of f so far, parameter used to avoid too local search
  double fmin, epsilon;
  // Objective function. We seek to **minimize** f. To maximize a function, specify -f
  functND f;
  // Number of variables in the optimization problem : float and integer
  size_t df, di;
  // Data provided to f
  void* data;
  // Current and maximal number of function evaluations
  unsigned int CurrEvals = 0, MaxEvals;
  // Current best candidate rectangle
  size_t BestRectangleSoFar;

  bool DivideRectangle(size_t id);

  std::vector<size_t> SelectRectanglesFromSlopes(const std::vector<size_t>& LCHIndices, const std::vector<Point2D >& DistanceValuesAtCenters);
  std::vector<size_t> PotentiallyOptimalRectangles();

  void InitialEvaluation();
  void CompareUpdate(double v, size_t id);

public:
  // Create a DIRECT object with parameters
  // f function to minimize
  // d number of variables
  // Lower bounds : point in R^d whose components are the lower bounds
  // Upper bounds : point in R^d whose components are the upper bounds
  // MaxEvals : Maximum number of evaluations of f
  // epsilon :
  // data :
  DIRECT(functND f_,PointMixed LowerBound_, PointMixed UpperBound_ , unsigned int MaxEvals_, void* data_ = NULL, double epsilon_ = 1e-8);
  PointMixed Optimize(void);
  // For testing purposes
#ifdef DIRECT_TESTING
  DIRECT(const std::vector<RectangleND>& list, functND f_, PointMixed LowerBound_, PointMixed UpperBound_);
  friend std::ofstream& operator<<(std::ofstream& os, const DIRECT& d);

#endif

#ifdef DEBUG
  void Postpro(void) {
    std::ofstream p("point.txt");
    for(size_t ii = 0; ii < RectangleList.size(); ii++) {
      p << RectangleList[ii].Center();
    }
  }
#endif
};

#endif
