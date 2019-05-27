#include "DIRECT.hpp"
DIRECT::DIRECT(functND f_, size_t d_, PointND LowerBound_, PointND UpperBound_ , unsigned int MaxEvals_, double epsilon_, void* data_)
 {
    f = f_;
    d = d_;
    LowerBound = LowerBound_;
    UpperBound = UpperBound_;
    CurrEvals = 0;
    epsilon = epsilon_;
    MaxEvals = MaxEvals_;
    data = data_;
    // Initialize RectangleList with the unit hypercube
    RectangleList.push_back(RectangleND(PointND(d, .5), PointND(d, .5), d));
  }

void DIRECT::InitialEvaluation(void)
 {
    fmin = RectangleList[0].EvalAtCenter(f, LowerBound, UpperBound, data);
    CurrEvals++;
    BestRectangleSoFar = 0;
  }

PointND DIRECT::Optimize(void)
 {
   InitialEvaluation();
   std::ofstream history("resu/history.txt");
   while(CurrEvals < MaxEvals) {
     std::vector<size_t> POR = PotentiallyOptimalRectangles();
     while(!POR.empty()) {
       size_t id_selected = POR.back();
       DivideRectangle(id_selected);
       {
	 PointND pp(d);
	 for(size_t ii = 0; ii < d; ii++) {
	   pp[ii] = RectangleList[BestRectangleSoFar].Center()[ii] * (UpperBound[ii] - LowerBound[ii]) + LowerBound[ii];
	 }
	 std::cout << "BestRectangleSoFar = " << BestRectangleSoFar << " fmin =  " << fmin << " at "<< std::endl << pp << std::endl;
	 history << fmin << std::endl;
       }
       POR.pop_back();
     }
   }
   return RectangleList[BestRectangleSoFar].Center();
 }
