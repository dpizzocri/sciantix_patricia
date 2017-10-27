//////////////////////////////////////////////////
//                                              //
//           S C I A N T I X                    //
//           ---------------                    //
//                                              //
//  Version: 0.1                                //
//  Year   : 2016                               //
//  Authors: D. Pizzocri, T. Barani, A. Magni   //
//                                              //
//////////////////////////////////////////////////

/// GasDiffusion
/// This function evaluates the fission gas concentrations
/// in irradiation/annealing conditions.

#include "GasDiffusion.h"

void GasDiffusion( )
{
  // diffusion coefficient
  double diffusion_coefficient = GasDiffusionCoefficient(Temperature[0], Fissionrate[0]);

  // trapping rates
  // calculated here because common for both irradiation and annealing conditions
  double trapping_rate(0.0);
  double trapping_rate_bubble_at_dislocations(0.0);
  double trapping_rate_dislocations(0.0);
  double dislocation_influence_radius(0.0);

  trapping_rate = TrappingRate(diffusion_coefficient, Intragranular_bubble_radius[0], Intragranular_bubble_concentration[0]);
  if (igas_precipitation_at_dislocations)
  {
    trapping_rate_bubble_at_dislocations = TrappingRate(diffusion_coefficient, Intragranular_bubble_radius_at_dislocations[0], Intragranular_bubble_concentration_at_dislocations[0]);
    dislocation_influence_radius = DislocationRadiusOfInfluence( );
    trapping_rate_dislocations = TrappingRateAtDislocations(diffusion_coefficient, dislocation_influence_radius);
  }

  // gas diffusion calculations
  if(Fissionrate[1] > 0.0)
  {
    fannealing[1] = 0;
	GasDiffusionIrradiation(diffusion_coefficient, trapping_rate, trapping_rate_bubble_at_dislocations, trapping_rate_dislocations);
  }
  else
  {
  	fannealing[1] = 1;
	GasDiffusionAnnealing(diffusion_coefficient, trapping_rate, trapping_rate_bubble_at_dislocations, trapping_rate_dislocations);
  }
}

