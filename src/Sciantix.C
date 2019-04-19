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

#include "Sciantix.h"
#include <iostream>
void Sciantix(int Sciantix_options[],
              double Sciantix_history[],
              double Sciantix_variables[],
              double Sciantix_scaling_factors[])
{
  SetVariables(Sciantix_options,
               Sciantix_history,
               Sciantix_variables,
               Sciantix_scaling_factors);

  FuelDensity( );

  NuclidesEvolution( );

  OxygenToMetalRatio( );

  Burnup( );

  FuelMicroStructure( );

  InertGasBehavior( );

  UpdateVariables(Sciantix_variables);
}
