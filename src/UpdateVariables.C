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

#include "UpdateVariables.h"

void UpdateVariables(double Sciantix_variables[])
{
  Sciantix_variables[0] = Grain_radius[1];
  Sciantix_variables[1] = Gas_produced[1];
  Sciantix_variables[2] = Gas_grain[1];
  Sciantix_variables[3] = Gas_grain_solution[1];
  Sciantix_variables[4] = Gas_grain_bubbles[1];
  Sciantix_variables[5] = Gas_boundary[1];
  Sciantix_variables[6] = Gas_released[1];
  Sciantix_variables[7] = Intragranular_bubble_concentration[1];
  Sciantix_variables[8] = Intragranular_bubble_radius[1];
  Sciantix_variables[9] = Intragranular_gas_swelling[1];
  Sciantix_variables[10] = Intergranular_bubble_concentration[1];
  Sciantix_variables[11] = Intergranular_atoms_per_bubble[1];
  Sciantix_variables[12] = Intergranular_vacancies_per_bubble[1];
  Sciantix_variables[13] = Intergranular_bubble_radius[1];
  Sciantix_variables[14] = Intergranular_bubble_area[1];
  Sciantix_variables[15] = Intergranular_bubble_volume[1];
  Sciantix_variables[16] = Intergranular_fractional_coverage[1];
  Sciantix_variables[17] = Intergranular_saturation_fractional_coverage[1];
  Sciantix_variables[18] = Intergranular_gas_swelling[1];
  Sciantix_variables[19] = Intergranular_fractional_intactness[1];
  Sciantix_variables[20] = Burn_up[1];
  Sciantix_variables[21] = Effective_burn_up[1];
}
