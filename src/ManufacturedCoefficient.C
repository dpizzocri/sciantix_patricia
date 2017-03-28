///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 0.1                         //
//  Year   : 2016                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

/// ManufacturedCoefficient
/// This namespace contains the manufactured coefficients [1]
/// used for verification purpose.
/// [1] Salari and Knupp, 2000, SAND2000-1444

#include "ManufacturedCoefficient.h"

namespace ManufacturedCoefficient
{
  void Sin(double constants[], double time, double &coefficient)
  {
    coefficient = sin(constants[4] * time);
  }

  void Sin2(double constants[], double time, double &coefficient)
  {
    coefficient = pow(sin(constants[4] * time), 2);
  }
}
