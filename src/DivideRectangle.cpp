#include "DIRECT.hpp"

std::vector<PreSplit> DIRECT::SortByEvals(size_t id, double delta, const std::vector<size_t>& AlongDimension) {
    const size_t n = AlongDimension.size();
    std::vector<PreSplit> DimValue(n);
    const RectangleND Rect = RectangleList[id];
    for(size_t ii = 0; ii < n; ii++) {
      // Adjacent 2 rectangles
      for(int jj = 0; jj < 2; jj++) {
	int dj = 2*jj-1;
	// NewRect creation
	RectangleND NewRect  = RectangleND(d);
	for(size_t dim = 0; dim < d; dim++) {
	  if(dim == AlongDimension[ii]) {
	    NewRect.Center(dim) = Rect.Center(dim) + 2*dj*delta;
	  } else {
	    NewRect.Center(dim) = Rect.Center(dim);
	  }
	} // End NewRect creation
	DimValue[ii][jj] = NewRect.EvalAtCenter(f, LowerBound, UpperBound, data);
	DimValue[ii].SetDimension(AlongDimension[ii]);
      }
    }
    CompareEvals(DimValue);
    return DimValue;
  }


void DIRECT::DivideRectangleFinal(size_t id, double delta, const std::vector<PreSplit>& PreSplitValues) {
  const RectangleND Rect = RectangleList[id];
  const size_t nd = PreSplitValues.size();
  for(size_t ii = 0; ii < nd; ii++) {
    const size_t CurrDim = PreSplitValues[ii].GetDimension();
    // Modifiy the geometry of the RectangleList[id]
    Flatten(RectangleList[id], CurrDim);
    // Add two rectangles from the split
    for(int jj = 0; jj < 2; jj++) {
      RectangleND NewRect(Rect, PreSplitValues[ii][jj], CurrDim, jj);
      RectangleList.push_back(NewRect);
      if(PreSplitValues[ii][jj] < fmin) {
	BestRectangleSoFar = RectangleList.size()-1;
	fmin = PreSplitValues[ii][jj];
      }
      CurrEvals++;
    }
  }
}

void DIRECT::DivideRectangle(size_t id)
{
  double delta;
  const std::vector<size_t> AlongDimension = RectangleList[id].LongestHalfSideDimensions(delta);
  const std::vector<PreSplit> PreSplitValues = SortByEvals(id, delta, AlongDimension);
  DivideRectangleFinal(id, delta, PreSplitValues);
}
