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

/// GasDiffusionAnnealing
/// This function calls the SpectralDiffusion solver
/// to evaluate the fission gas concentration
/// inside the single grain after a fixed time step,
/// in annealing conditions.
/// Typical numerical values for UO2 fuel are taken from:
/// [1] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109

#include "GasDiffusionAnnealing.h"

void GasDiffusionAnnealing(double diffusion_coefficient, double trapping_rate, double trapping_rate_bubble_at_dislocations, double trapping_rate_dislocations)
{
	const unsigned short int N(20);
  	static std::vector<double> gas_solution_modes(N, 0.0);

  	if (fannealing[0] == 0 && fannealing[1] == 1)
  	{
      unsigned short int index(0);
      unsigned short int mode_index(0);

      for (index = 0; index < N; index++)
      {
    	mode_index = index + 1;
		gas_solution_modes[index] = (- 2.0 * Grain_radius[1] * sqrt(2.0 * Grain_radius[1] / Pi) * pow(- 1.0, mode_index) / mode_index) * Gas_grain_solution[1];
      }
	}

  	const double fission_yield = Fission_yield_Xe + Fission_yield_Kr;
	double source_term = fission_yield * Fissionrate[1]; // (at/m3-s)

	double trapping_rate_spectral = 0.0;

    if (igas_precipitation_at_dislocations)
	  trapping_rate_spectral = trapping_rate
	                         + trapping_rate_bubble_at_dislocations
	                         + trapping_rate_dislocations;

  	switch(idiffusion_solver)
  	{
  		case 0 :
  			Gas_grain_solution[1] = Solver::SpectralDiffusion(gas_solution_modes, N, diffusion_coefficient, trapping_rate_spectral, Grain_radius[1], source_term, dTime_s);
  			break;

  		default :
        	ErrorMessages::Switch("GasDiffusion", "idiffusion_solver", idiffusion_solver);
        	break;
  	}

    Gas_grain_bubbles[1] = Solver::Integrator(Gas_grain_bubbles[0], trapping_rate*Gas_grain_solution[1], dTime_s);
  	Gas_grain_dislocations[1] = Solver::Integrator(Gas_grain_dislocations[0], (trapping_rate_bubble_at_dislocations + trapping_rate_dislocations)*Gas_grain_solution[1], dTime_s);
  	Gas_grain[1] = Gas_grain_solution[1] + Gas_grain_bubbles[1] + Gas_grain_dislocations[1];
  	Gas_boundary[1] = Gas_produced[1] - Gas_grain[1];
}

