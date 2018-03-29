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

  Burnup( );

  FuelMicroStructure( );

  InertGasBehavior( );

  UpdateVariables(Sciantix_variables);
}
