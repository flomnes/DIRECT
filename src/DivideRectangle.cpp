#include "DIRECT.hpp"

bool DIRECT::DivideRectangle(size_t id) {
#ifdef DEBUG
  std::cout << "DivideRectangle id =" << id << std::endl;
#endif
  const RectangleND R = RectangleList[id];
  const int dir0 = R.LargestAdmissibleDirection();
  if(dir0 == -1)
    return false;
  const unsigned int dir = dir0;
#ifdef DEBUG
  std::cout << "Divide in direction " << dir << std::endl;
#endif
  // Divide in float direction
  unsigned int id_last;
  if(dir < R.DimensionFloat()) {
    RectangleList[id].NumberDivisions(dir)++;
    for(int ii = -1; ii < 2; ii+=2) {
      RectangleND NewR = R.CopySideFloat(dir, ii);
      double v = NewR.EvalAtCenter(f, LowerBound, UpperBound, data);
      RectangleList.push_back(NewR);
      id_last = RectangleList.size()-1;
      CurrEvals++;
      CompareUpdate(v, id_last);
    }
  } else { // Divide in integer direction
    const int delta = R.ComputeDelta(dir);
    int lowInd;
    if(delta >= 1)
      lowInd = -1;
    else
      lowInd = 0;
    for(int jj = lowInd; jj < 2; jj++) {
      RectangleND NewR = R.CopySideInteger(dir, delta, jj);
      double v;
      if(jj != 0) {
	v = NewR.EvalAtCenter(f, LowerBound, UpperBound, data);
	RectangleList.push_back(NewR);
	id_last = RectangleList.size()-1;
	CurrEvals++;
	CompareUpdate(v, id_last);
      } else {
	RectangleList[id] = NewR;
      }
    }
  }
  return true;
}
