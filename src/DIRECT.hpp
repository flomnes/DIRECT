#ifndef DIRECT_HPP
#define DIRECT_HPP

#include <vector>
#ifdef DEBUG
#include <iostream>
#include <fstream>
#include <string>
#endif
#include "PreSplitContainer.hpp"
#include "RectangleND.hpp"
#include "ConvexHull.hpp"
#include "Point2D.hpp"
#include "typedefs.hpp"


class DIRECT {
private:
  // List of rectangles built by DIRECT algorithm, in the hypercube [0,1]^d
  std::vector<RectangleND > RectangleList;
  // Bounds imposed on variables in the optimization problem
  PointND LowerBound, UpperBound;
  // Minimum value of f so far, parameter used to avoid too local search
  double fmin, epsilon;
  // Objective function. We seek to **minimize** f. To maximize a function, specify -f
  functND f;
  // Number of variables in the optimization problem
  size_t d;
  // Data provided to f
  void* data;
  // Current and maximal number of function evaluations
  unsigned int CurrEvals = 0, MaxEvals;
  // Current best candidate rectangle
  size_t BestRectangleSoFar;
  // Split rectangle id into 3 rectangles along a specified dimension
  // Add 2 new rectangle into RectangleList. Keep original rectangle, only change its length along specified dimension

  void DivideRectangle(size_t id);
  void DivideRectangleFinal(size_t id, double delta, const std::vector<PreSplit>& PreSplitValues);
  std::vector<PreSplit> SortByEvals(size_t id, double delta, const std::vector<size_t>& AlongDimension);

  std::vector<size_t> SelectRectanglesFromSlopes(const std::vector<size_t>& LCHIndices, const std::vector<Point2D >& DistanceValuesAtCenters);
  std::vector<size_t> PotentiallyOptimalRectangles(void);

  void InitialEvaluation(void);


public:
  // Create a DIRECT object with parameters
  // f function to minimize
  // d number of variables
  // Lower bounds : point in R^d whose components are the lower bounds
  // Upper bounds : point in R^d whose components are the upper bounds
  // MaxEvals : Maximum number of evaluations of f
  // epsilon :
  // data :
  DIRECT(functND f_, size_t d_, PointND LowerBound_, PointND UpperBound_ , unsigned int MaxEvals_, double epsilon_ = 1e-8, void* data_ = NULL);
  PointND Optimize(void);


#ifdef DEBUG
  void Postpro(void) {
    std::ofstream p("point.txt");
    for(size_t ii = 0; ii < RectangleList.size(); ii++) {
      for(size_t jj = 0; jj < d; jj++)
	p << RectangleList[ii].Center(jj) << " ";
    p << std::endl;
    }
  }
#endif
};

#endif
