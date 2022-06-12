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
              double Sciantix_scaling_factors[],
              double Sciantix_diffusion_modes[])
{
  SetVariables(Sciantix_options,
               Sciantix_history,
               Sciantix_variables,
               Sciantix_scaling_factors,
               Sciantix_diffusion_modes);

  FuelDensity( );

//  NuclidesEvolution( );

  OxygenToMetalRatio( );

  Burnup( );

  FuelMicroStructure( );

  InertGasBehavior( );

  UpdateVariables(Sciantix_variables, Sciantix_diffusion_modes);
}
