#include "DIRECT.hpp"
#include <cassert>
DIRECT::DIRECT(functND f_, PointMixed LowerBound_, PointMixed UpperBound_ , unsigned int MaxEvals_, double epsilon_, void* data_)
 {
   assert(LowerBound_.first.Dimension() == UpperBound_.first.Dimension());
   assert(LowerBound_.second.Dimension() == UpperBound_.second.Dimension());
   df = LowerBound_.first.Dimension();
   di = LowerBound_.second.Dimension();
   f = f_;
   LowerBound = LowerBound_;
   UpperBound = UpperBound_;

   CurrEvals = 0;
   epsilon = epsilon_;
   MaxEvals = MaxEvals_;
   data = data_;
   // Initialize RectangleList with the unit hypercube
   RectangleList.push_back(RectangleND(LowerBound, UpperBound));
  }

void DIRECT::InitialEvaluation()
 {
    fmin = RectangleList[0].EvalAtCenter(f, LowerBound, UpperBound, data);
    CurrEvals++;
    BestRectangleSoFar = 0;
  }

void DIRECT::CompareUpdate(double v, size_t id) {
  if(v < fmin) {
    BestRectangleSoFar = id;
    fmin = v;
  }
}

PointMixed DIRECT::Optimize()
 {
   InitialEvaluation();
   std::ofstream history("resu/history.txt");
   while(CurrEvals < MaxEvals) {
     std::vector<size_t> POR = PotentiallyOptimalRectangles();
     while(!POR.empty()) {
       size_t id_selected = POR.back();
       DivideRectangle(id_selected);
       {
	 std::cout << "BestRectangleSoFar = " << BestRectangleSoFar << " fmin =  " << fmin << " at "<< std::endl << RectangleList[BestRectangleSoFar].Center(LowerBound, UpperBound) << std::endl;
	 history << fmin << std::endl;
       }
       POR.pop_back();
     }
   }
   return RectangleList[BestRectangleSoFar].Center(LowerBound, UpperBound);
 }
