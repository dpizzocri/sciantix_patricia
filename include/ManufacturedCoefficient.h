///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

#include <cmath>

namespace ManufacturedCoefficient
{
  void Sin(double constants[], double time, double &coefficient);

  void Sin2(double constants[], double time, double &coefficient);

  void HilbertMatrix2x2(double A[]);

  void HilbertMatrix3x3(double A[]);

  void HilbertMatrix(int N, double A[]);
};
