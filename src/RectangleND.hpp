#ifndef DIRECT_RECTANGLE_ND_HPP
#define DIRECT_RECTANGLE_ND_HPP

#include <cmath>
#include <cassert>
#include "PointND.hpp"
#include "typedefs.hpp"
#include "EvalFunctionND.hpp"
#include "RectangleFloat.hpp"
#include "RectangleInteger.hpp"



class RectangleND {
private:
  // Integer rectangle
  RectangleInteger RI;
  // Float rectangle
  RectangleFloat RF;
  // Function value at center
  double v;
public:
  RectangleND CopySideFloat(size_t dir, char side) const {
    const double l = LengthDirection(dir);
    RectangleFloat NewRF = RF;
    NewRF.NumberDivisions(dir)++;
    NewRF.Center(dir) = RF.Center(dir) + side*(l/3);
    return Copy(NewRF);
  }

  RectangleND CopySideInteger(size_t dir, int delta, char side) const {
    RectangleInteger NewRI = RI;
    dir -= DimensionFloat();
    NewRI.NumberDivisions(dir)++;
    const int a = NewRI(dir, 0);
    const int b = NewRI(dir, 1);
    bool ReturnVal = false;
    if(delta >=1) {
      switch(side) {
      case -1:
	NewRI(dir, 0) = a;
	NewRI(dir, 1) = a+delta-1;
	break;
      case 0:
	NewRI(dir, 0) = a+delta;
	NewRI(dir, 1) = b-delta;
	ReturnVal = true;
	break;
      case 1:
	NewRI(dir, 0) = b-delta+1;
	NewRI(dir, 1) = b;
	break;
      default:
	std::cerr << "Unexpected side value" << std::endl;
	exit(1);
      }
    } else {
      switch(side) {
      case 0:
	NewRI(dir, 0) = a;
	NewRI(dir, 1) = a;
	ReturnVal = true;
	break;
      case 1:
	NewRI(dir, 0) = b;
	NewRI(dir, 1) = b;
	break;
      default:
	std::cerr << "Unexpected side value" << std::endl;
	exit(1);
      }
    }
    if(ReturnVal)
      return Copy(NewRI);
    else
      return Copy(NewRI, v);
  }

  RectangleND(const PointMixed& LowerBound, const PointMixed& UpperBound) {
    const size_t dimFloat = LowerBound.first.Dimension();
    RF = RectangleFloat(PointND<double>(dimFloat, 0), PointND<double>(dimFloat,1));
    RI = RectangleInteger(LowerBound.second, UpperBound.second);
  }

  RectangleND(const RectangleInteger& RI_, const RectangleFloat& RF_, double v_) {
    RI = RI_;
    RF = RF_;
    v = v_;
  }

  RectangleND(const RectangleInteger& RI_, const RectangleFloat& RF_) {
    RI = RI_;
    RF = RF_;
  }

  int ComputeDelta(size_t dir) const {
    assert(dir >= DimensionFloat());
    dir -= DimensionFloat();
    return RI.ComputeDelta(dir);
  }

  RectangleInteger GetRI() const {
    return RI;
  }

  RectangleFloat GetRF() const {
    return RF;
  }

  RectangleND Copy(const RectangleInteger& RI_) const {
    return RectangleND(RI_, RF);
  }

  RectangleND Copy(const RectangleInteger& RI_, double v_) const {
    return RectangleND(RI_, RF, v_);
  }


  RectangleND Copy(const RectangleFloat& RF_) const {
    return RectangleND(RI, RF_);
  }

  PointMixed Center() const {
    return std::make_pair(RF.Center(), RI.Center());
  }

  PointMixed Center(const PointMixed& LowerBound, const PointMixed& UpperBound) const {
    const PointMixed x = Center();
    const size_t df = x.first.Dimension();
    PointMixed xis = std::make_pair(PointND<>(df), x.second);
    for(size_t ii = 0; ii < df; ii++) {
      xis.first[ii] = x.first[ii] * (UpperBound.first[ii] - LowerBound.first[ii]) + LowerBound.first[ii];
   }
    return xis;
  }

  size_t DimensionFloat() const {
    return RF.Dimension();
  }

  size_t DimensionInteger() const {
    return RI.Dimension();
  }

  size_t Dimension() const {
    return DimensionFloat() + DimensionInteger();
  }

  unsigned int NumberDivisions(size_t dim) const {
    if((dim) < DimensionFloat()) {
      return RF.NumberDivisions(dim);
    } else {
      dim -= DimensionFloat();
      return RI.NumberDivisions(dim);
    }
  }


  unsigned int& NumberDivisions(size_t dim) {
    if((dim) < DimensionFloat()) {
      return RF.NumberDivisions(dim);
    } else {
      dim -= DimensionFloat();
      return RI.NumberDivisions(dim);
    }
  }

  // RectangleND CopyLeftFloat(size_t dir) const {
  //   return CopySideFloat(dir, -1);
  // }

  // RectangleND CopyRightFloat(size_t dir) const {
  //   return CopySideFloat(dir, 1);
  // }

  bool IsDirectionAdmissible(size_t dim) const {
    if(dim < DimensionFloat()) {
      return true;
    } else {
      dim -= DimensionFloat();
      return RI.IsDirectionAdmissible(dim);
    }
  }

  // Returns a vector containing the largest admissible directions
  // Any float direction is admissible
  // An integer direction is admissible only if it contains two points or more

  int LargestAdmissibleDirection() const {
    const size_t dim = Dimension();
    // Get value of largest (i.e least divided) direction
    unsigned int ii = 0;
    int r;
    while(!IsDirectionAdmissible(ii)) {
      ii++;
    }
    if(ii >= dim)
      return -1;
    //    assert(ii < dim && "No admissible direction for rectangle division");
    r = ii;
    unsigned int smallestdim = NumberDivisions(ii);
    for(ii = 0; ii < dim; ii++) {
      if(!IsDirectionAdmissible(ii))
	continue;
      if(smallestdim > NumberDivisions(ii)) {
	smallestdim = NumberDivisions(ii);
	r = ii;
      }
    }
    return r;
  }

  bool IsDivisible() {
    bool r = false;
    for(size_t ii = 0; ii < Dimension(); ii++) {
      if(IsDirectionAdmissible(ii))
	r = true;
    }
    return r;
  }

  double Distance() {
    double r = 0;
    for(unsigned int ii = 0; ii < DimensionFloat(); ii++) {
      r+=std::pow(1./3, RF.NumberDivisions(ii));
    }
    for(unsigned int ii = 0; ii < DimensionInteger(); ii++) {
      r+=std::pow(1./3, RI.NumberDivisions(ii));
    }
    return std::sqrt(r);
  }

  double LengthDirection(size_t dir) const {
    if(dir < DimensionFloat()) {
      return std::pow(1./3, RF.NumberDivisions(dir));
    } else {
      dir -= DimensionFloat();
      return std::pow(1./3, RI.NumberDivisions(dir));
    }
  }

  double EvalAtCenter(functND f, const PointMixed& LowerBound, const PointMixed& UpperBound, const void* data) {
    const PointMixed c = Center(LowerBound, UpperBound);
    v = EvalFunctionND(f, c, data);
    return v;
  }

  double ValueAtCenter() {
    return v;
  }
#ifdef DIRECT_TESTING
  friend std::ostream& operator<<(std::ostream& os, const RectangleND& R);
#endif
};

#endif
