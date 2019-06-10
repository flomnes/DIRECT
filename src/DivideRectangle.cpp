#include "DIRECT.hpp"

void DIRECT::DivideRectangle(size_t id) {
#ifdef DEBUG
  std::cout << "DivideRectangle id =" << id << std::endl;
#endif
  const RectangleND R = RectangleList[id];
  const size_t dir = R.LargestAdmissibleDirection();
#ifdef DEBUG
  std::cout << "Divide in direction " << dir << std::endl;
#endif
  // Divide in float direction
  if(dir < R.DimensionFloat()) {
    RectangleND NewR = R.CopyLeftFloat(dir);
    double v = NewR.EvalAtCenter(f, LowerBound, UpperBound, data);
    RectangleList.push_back(NewR);
    id++;
    CurrEvals++;
    CompareUpdate(v, id);

    NewR = R.CopyRightFloat(dir);
    v = NewR.EvalAtCenter(f, LowerBound, UpperBound, data);
    RectangleList.push_back(NewR);
    id++;
    CurrEvals++;
    CompareUpdate(v, id);

    RectangleList[id].NumberDivisions(dir)++;
  } else { // Divide in integer direction
    const int delta = R.ComputeDelta(dir);
    int lowInd;
    if(delta >= 1) {
      lowInd = -1;
    } else {
      lowInd = 0;
    }
    for(int jj = lowInd; jj < 2; jj++) {
      RectangleND NewR = R.CopySideInteger(dir, delta, jj);
      if(jj==0) {
	RectangleList[id] = NewR;
      } else {
	double v = NewR.EvalAtCenter(f, LowerBound, UpperBound, data);
	RectangleList.push_back(NewR);
	id++;
	CurrEvals++;
	CompareUpdate(v, id);
      }
    }
  }
}
