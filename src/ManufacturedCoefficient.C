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

/// ManufacturedCoefficient
/// This namespace contains the manufactured coefficients [1]
/// used for verification purpose.
/// [1] Salari and Knupp, 2000, SAND2000-1444

#include "ManufacturedCoefficient.h"
#include <iostream>

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

  void HilbertMatrix2x2(double A[])
  {
    A[0] = 1.0;
    A[1] = 0.5;
    A[2] = 0.5;
    A[3] = 1.0/3.0;
  }

  void HilbertMatrix3x3(double A[])
  {
    A[0] = 1.0;
    A[1] = 0.5;
    A[2] = 1.0/3.0;
    A[3] = 0.5;
    A[4] = 1.0/3.0;
    A[5] = 0.25;
    A[6] = 1.0/3.0;
    A[7] = 0.25;
    A[8] = 0.2;
  }

  void HilbertMatrix(int N, double A[])
  {
    //int N = 5;
    //double A[N*N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[j*N + i] = 1.0/(2.0+i+j);
        }
    }
//    for (int c = 0; c < N; c++){
//        for (int r = 0; r < N; r++){
//            std::cout << A[c*N + r] << "  ";
//        }
//        std::cout << "\n";
    }
  }
