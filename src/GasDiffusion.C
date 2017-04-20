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

/// GasDiffusion
/// This function calls the solver SpectralDiffusion
/// to evaluate the fission gas concentration
/// inside the single grain after a fixed time step.

#include "GasDiffusion.h"

double GasDiffusion( )
{
  const unsigned short int N(5);
  const double gas_grain_initial(0.0);
  static std::vector<double> gas_grain_modes(N, gas_grain_initial);
  double grain_radius(1.0);
  double source_term(15.0);
  double time_step(1.0e20);
  double gas_grain_concentration(gas_grain_initial);
  
  double diffusion_coefficient = GasDiffusionCoefficient(1.0, 1.0);
  
  gas_grain_concentration = Solver::SpectralDiffusion(gas_grain_modes, N, diffusion_coefficient, grain_radius, source_term, time_step);
  std::cout << gas_grain_concentration;
  return gas_grain_concentration;
}
