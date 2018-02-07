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

/// GasDiffusion
/// This function calls the solver SpectralDiffusion
/// to evaluate the fission gas concentration
/// inside the single grain after a fixed time step.
/// Typical numerical values for UO2 fuel are taken from:
/// [1] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109

#include "GasDiffusion.h"

void GasDiffusion( )
{
  double diffusion_coefficient = GasDiffusionCoefficient(Temperature[0], Fissionrate[0]);
  double resolution_rate = ResolutionRate(Intragranular_bubble_radius[0], Fissionrate[0]);
  double trapping_rate = TrappingRate(diffusion_coefficient, Intragranular_bubble_radius[0], Intragranular_bubble_concentration[0]);
  double equilibrium_fraction = resolution_rate / (resolution_rate + trapping_rate);
  double effective_diffusion_coefficient = diffusion_coefficient * equilibrium_fraction;

  const unsigned short int N(20);
  static std::vector<double> gas_grain_modes(N, 0.0);
  double initial_condition = 0.0;
  static double initial_condition_term[4] = {initial_condition, initial_condition, initial_condition, initial_condition};
  
  const double fission_yield = Fission_yield_Xe + Fission_yield_Kr;
  double source_term = fission_yield * Fissionrate[1]; // (at/m3-s)
  
  switch(isolver)
  {
  	case 0 :
  		Gas_grain[1] = Solver::SpectralDiffusion(gas_grain_modes, N, effective_diffusion_coefficient, Grain_radius[1], source_term, dTime_s);
  		break;
  		
  	case 1 :
  		Gas_grain[1] = Solver::FORMAS(initial_condition_term, effective_diffusion_coefficient, Grain_radius[1], source_term, dTime_s);
  		break;
  		
  	default :
        ErrorMessages::Switch("GasDiffusion", "isolver", isolver);
        break;
  }
  
  Gas_grain_solution[1] = Gas_grain[1] * equilibrium_fraction;
  Gas_grain_bubbles[1] = Gas_grain[1] * (1.0 - equilibrium_fraction);
  Gas_boundary[1] = Gas_produced[1] - Gas_grain[1];
}
