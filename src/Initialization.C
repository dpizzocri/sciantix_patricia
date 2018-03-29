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

  Sciantix_variables[0] = 5.0e-06;
  Sciantix_variables[1] = 0.0;
  Sciantix_variables[2] = 0.0;
  Sciantix_variables[3] = 0.0;
  Sciantix_variables[4] = 0.0;
  Sciantix_variables[5] = 0.0;
  Sciantix_variables[6] = 0.0;
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

  Sciantix_scaling_factors[0] = 1.0;
  Sciantix_scaling_factors[1] = 1.0;
  Sciantix_scaling_factors[2] = 1.0;
  Sciantix_scaling_factors[3] = 1.0;
}
