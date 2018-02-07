#include "Initialization.h"

void Initialization( )
{
  Sciantix_history[0] = Temperature_input[0];
  Sciantix_history[2] = Fissionrate_input[0];
  Sciantix_history[4] = Hydrostaticstress_input[0];
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
}
