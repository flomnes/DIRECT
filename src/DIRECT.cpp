#include "DIRECT.hpp"
#include <cassert>
DIRECT::DIRECT(functND f_, PointMixed LowerBound_, PointMixed UpperBound_ , unsigned int MaxEvals_, void* data_, double epsilon_)
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
  }

void DIRECT::InitialEvaluation()
 {
   // Initialize RectangleList with the unit hypercube only for continuous variables
   RectangleList.push_back(RectangleND(LowerBound, UpperBound));

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
   bool r = true;
   while(CurrEvals < MaxEvals) {
     std::vector<size_t> POR = PotentiallyOptimalRectangles();
#ifdef DEBUG
     std::cout << "Potentially optimal rectangles" << std::endl;
     display(std::cout,POR);
#endif
     if(POR.size() == 0) {
       std::cout << "No rectangle can be divided, stopping execution" << std::endl;
       break; // No more dividible rectangles, stop execution
     }
     while(!POR.empty()) {
       size_t id_selected = POR.back();
       r = DivideRectangle(id_selected);
       if(r == false)
	 break;
       {
	 std::cout << "BestRectangleSoFar = " << BestRectangleSoFar << " fmin =  " << fmin << " at "<< std::endl << RectangleList[BestRectangleSoFar].Center(LowerBound, UpperBound) << std::endl;
	 history << fmin << std::endl;
       }
       POR.pop_back();
     }
     if(r==false)
       break;
   }
   return RectangleList[BestRectangleSoFar].Center(LowerBound, UpperBound);
 }
