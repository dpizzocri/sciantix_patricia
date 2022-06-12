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

/// Initialization
/// This routine initializes Sciantix internal variables with
/// initial conditions/interface variables

#include "Initialization.h"

void Initialization( )
{
  Sciantix_history[0] = Temperature_input[0];
  Sciantix_history[1] = Temperature_input[0];
  Sciantix_history[2] = Fissionrate_input[0];
  Sciantix_history[3] = Fissionrate_input[0];
  Sciantix_history[4] = Hydrostaticstress_input[0];
  Sciantix_history[5] = Hydrostaticstress_input[0];
  Sciantix_history[6] = 0.0;

  Sciantix_variables[7] = 0.0;
  Sciantix_variables[8] = 0.0;
  Sciantix_variables[9] = 0.0;
  Sciantix_variables[10] = 4.0e+13;
  Sciantix_variables[11] = 0.0;
  Sciantix_variables[12] = 0.0;
  Sciantix_variables[13] = 1.0e-08;
  Sciantix_variables[14] = 0.0;
  Sciantix_variables[15] = 0.0;
  Sciantix_variables[16] = 0.0;
  Sciantix_variables[17] = 0.5;
  Sciantix_variables[18] = 0.0;
  Sciantix_variables[19] = 1.0;
  Sciantix_variables[20] = 0.0;
  Sciantix_variables[21] = 0.0;

  double Mmol_HM = 0.01 * (
                Sciantix_variables[61] * 234.04 + Sciantix_variables[62] * 235.04 + Sciantix_variables[63] * 236.05 + Sciantix_variables[64] * 237.05 + Sciantix_variables[65] * 238.05 +
                Sciantix_variables[66] * 237.04 + Sciantix_variables[67] * 238.05 + Sciantix_variables[68] * 239.05 +
                Sciantix_variables[69] * 238.05 + Sciantix_variables[70] * 239.05 + Sciantix_variables[71] * 240.05 + Sciantix_variables[72] * 241.06 + Sciantix_variables[72] * 242.06 + Sciantix_variables[73] * 243.06 +
                Sciantix_variables[75] * 241.06 + Sciantix_variables[76] * 242.06 + Sciantix_variables[77] * 242.06 + Sciantix_variables[78] * 243.06 + Sciantix_variables[78] * 244.06 +
                Sciantix_variables[80] * 242.06 + Sciantix_variables[81] * 243.06 + Sciantix_variables[82] * 244.06 + Sciantix_variables[83] * 245.07
                );

  double HM_HMO2 = Mmol_HM / (Mmol_HM + 32.0); // Heavy Metals over Heavy Metal Oxides in mass

  double HM_m3 = 1000. * Sciantix_variables[84] * 6.022e+23 / (Mmol_HM + 32.0);

  for (int i = 24; i < 61; i++)
    Sciantix_variables[i] = 0.0;

  for (int j = 61; j < 83; j++)
    Sciantix_variables[j] *= 0.01 * HM_m3;

  Sciantix_variables[23] = HM_m3 * Sciantix_variables[85];

  // projection on diffusion modes of the initial conditions
  double initial_condition(0.0);
  double projection_remainder(0.0);
  double reconstructed_solution(0.0);
  int iteration(0), iteration_max(20), n(0), np1(1), n_modes(40), k(0), K(1);
  double projection_coeff(0.0);
  projection_coeff = - sqrt(8.0 / M_PI);

  for (k = 0; k < K; ++k)
  {
    switch (k)
		{
  		case 0  : initial_condition = Sciantix_variables[2]; break;     // Xe grain

    	default : initial_condition = 0.0; break;
		}

		projection_remainder = initial_condition;
		for (iteration = 0; iteration < iteration_max; ++iteration)
    {
      reconstructed_solution = 0.0;
      for (n = 0; n < n_modes; ++n)
      {
        np1 = n+1;
        const double n_coeff = pow(- 1.0, np1) / np1;
        Sciantix_diffusion_modes[k * n_modes + n] += projection_coeff * n_coeff * projection_remainder;
        reconstructed_solution += projection_coeff * n_coeff * Sciantix_diffusion_modes[k * n_modes + n] * 3.0 / (4.0 * M_PI);
      }
      projection_remainder = initial_condition - reconstructed_solution;
    }
  }

}
