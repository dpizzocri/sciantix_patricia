///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.0                         //
//  Year   : 2018                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

#include "Sciantix.h"
#include <iostream>

void Sciantix(int Sciantix_options[], double Sciantix_history[], double Sciantix_variables[], double Sciantix_scaling_factors[])
{
  InputStorage(Sciantix_options, Sciantix_history, Sciantix_variables, Sciantix_scaling_factors);

  std::cout << Fissionrate[1] << std::endl;

  if (igrain_growth) GrainGrowth( );

  if (iinert_gas_behavior) InertGasBehavior( );
}
