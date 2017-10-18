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

/// GasDiffusionIrradiation
/// This function calls the SpectralDiffusion solver
/// to evaluate the fission gas concentration
/// inside the single grain after a fixed time step,
/// in irradiation conditions.

#include "GasDiffusionIrradiation.h"

void GasDiffusionIrradiation(double diffusion_coefficient, double trapping_rate, double trapping_rate_bubble_at_dislocations, double trapping_rate_dislocations)
{
	double resolution_rate = ResolutionRate(Intragranular_bubble_radius[0], Fissionrate[0]);
	double intragranular_bubble_atomic_radius = IntraGranularBubbleRadius(Temperature[1], Intragranular_atoms_per_bubble_at_dislocations[0]);
  	double resolution_rate_bubble_at_dislocations = ResolutionRate(intragranular_bubble_atomic_radius, Fissionrate[0]);

  	const unsigned short int N(20);
  	static std::vector<double> gas_grain_modes(N, 0.0);

  	// transition from annealing to irradiation
  	if (fannealing[0] == 1 && fannealing[1] == 0)
    {
      unsigned short int index(0);
      unsigned short int mode_index(0);

      for (index = 0; index < N; index++)
      {
    	mode_index = index + 1;
		gas_grain_modes[index] = (- 2.0 * Grain_radius[1] * sqrt(2.0 * Grain_radius[1] / Pi) * pow(- 1.0, mode_index) / mode_index) * Gas_grain[0];
		resolution_rate = ResolutionRate(Intragranular_bubble_radius[0], Fissionrate[1]);
		resolution_rate_bubble_at_dislocations = ResolutionRate(intragranular_bubble_atomic_radius, Fissionrate[1]);
      }
    }

	double ratio_trap_res = trapping_rate / resolution_rate;
    double ratio_trap_res_at_dislocations = trapping_rate_dislocations / resolution_rate_bubble_at_dislocations;
    double ratio_trap_res_bubble_at_dislocations = trapping_rate_bubble_at_dislocations / resolution_rate_bubble_at_dislocations;

  	double equilibrium_fraction = 1.0 / (1.0 + ratio_trap_res
                                             + ratio_trap_res_at_dislocations
                                             + ratio_trap_res_bubble_at_dislocations);
  	double effective_diffusion_coefficient = diffusion_coefficient * equilibrium_fraction;

  	const double fission_yield = Fission_yield_Xe + Fission_yield_Kr;
	double source_term = fission_yield * Fissionrate[1]; // (at/m3-s)

	double trapping_rate_spectral = 0.0;

  	switch(idiffusion_solver)
  	{
      case 0 :
  		Gas_grain[1] = Solver::SpectralDiffusion(gas_grain_modes, N, effective_diffusion_coefficient, trapping_rate_spectral, Grain_radius[1], source_term, dTime_s);
  		break;

      default :
       	ErrorMessages::Switch("GasDiffusion", "idiffusion_solver", idiffusion_solver);
       	break;
  	}

  	Gas_grain_solution[1] = Gas_grain[1] * equilibrium_fraction;
  	Gas_grain_bubbles[1] = Gas_grain_solution[1] * (ratio_trap_res);
  	Gas_grain_dislocations[1] = Gas_grain_solution[1] * (ratio_trap_res_at_dislocations + ratio_trap_res_bubble_at_dislocations);
  	Gas_boundary[1] = Gas_produced[1] - Gas_grain[1];
}

