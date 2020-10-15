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

/// ManufacturedSolutions
/// This namespace contains the manufactured solutions [1]
/// used for verification purpose.
/// The manufactured functions are constructed
/// as products of elementary functions,
/// with arbitrary constants (set to 1.0 by default).
/// [1] Salari and Knupp, 2000, SAND2000-1444

#include "ManufacturedSolution.h"
#include <stdlib.h>

namespace ManufacturedSolution
{
  void SinExpPow(double constants[], double time, double &solution, double &derivative)
  {
    solution = sin(constants[0] * time)
             * exp(constants[1] * time)
             * pow(constants[2] * time, constants[3]);

    derivative =   (constants[0] * cos(constants[0] * time))
                 * (exp(constants[1] * time))
                 * (pow(constants[2] * time, constants[3]))
               +   (sin(constants[0] * time))
                 * (constants[1] * exp(constants[1] * time))
                 * (pow(constants[2] * time, constants[3]))
               +   (sin(constants[0] * time))
                 * (exp(constants[1] * time))
                 * (constants[3] * pow(constants[2] * time, constants[3]-1.0));
  }

  void CosExp(double constants[], double time, double &solution, double &derivative)
  {
    solution = cos(constants[0] * time)
             * exp(constants[1] * time);

    derivative =   (- constants[0] * sin(constants[0] * time))
                 * (exp(constants[1] * time))
               +   (cos(constants[0] * time))
                 * (constants[1] * exp(constants[1] * time));
  }

  void Vector1x2(double x[])
  {
    x[0] = -1.0/1000.0;
    x[1] = 1000.0;
  }

  void Vector1x3(double x[])
  {
    x[0] = -1.0/1000.0;
    x[1] = 1000.0;
    x[2] = 0.0;
  }

  void Vector1xN(int N, double x[])
  {
    x[0] = 0;
    for (int i = 1; i < N; i++) {
      srand(1);
      x[i] = rand() % 2000 - 1000;
    }
  }

}
