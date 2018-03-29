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

#include "SetVariables.h"

void SetVariables(int Sciantix_options[], double Sciantix_history[], double Sciantix_variables[], double Sciantix_scaling_factors[])
{
  iverification = Sciantix_options[0];
  igrain_growth = Sciantix_options[1];
  iinert_gas_behavior = Sciantix_options[2];
  igas_diffusion_coefficient = Sciantix_options[3];
  iintra_bubble_evolution = Sciantix_options[4];
  ibubble_radius = Sciantix_options[5];
  iresolution_rate = Sciantix_options[6];
  itrapping_rate = Sciantix_options[7];
  inucleation_rate = Sciantix_options[8];
  isolver = Sciantix_options[9];
  ioutput = Sciantix_options[10];
  igrain_boundary_vacancy_diffusion_coefficient = Sciantix_options[11];
  igrain_boundary_behaviour = Sciantix_options[12];
  igrain_boundary_micro_cracking = Sciantix_options[13];
  igrain_recrystallization = Sciantix_options[14];

  Temperature[0] = Sciantix_history[0];
  Temperature[1] = Sciantix_history[1];
  Fissionrate[0] = Sciantix_history[2];
  Fissionrate[1] = Sciantix_history[3];
  Hydrostaticstress[0] = Sciantix_history[4];
  Hydrostaticstress[1] = Sciantix_history[5];
  dTime_s = Sciantix_history[6];

  Grain_radius[0] = Sciantix_variables[0];
  Gas_produced[0] = Sciantix_variables[1];
  Gas_grain[0] = Sciantix_variables[2];
  Gas_grain_solution[0] = Sciantix_variables[3];
  Gas_grain_bubbles[0] = Sciantix_variables[4];
  Gas_boundary[0] = Sciantix_variables[5];
  Gas_released[0] = Sciantix_variables[6];
  Intragranular_bubble_concentration[0] = Sciantix_variables[7];
  Intragranular_bubble_radius[0] = Sciantix_variables[8];
  Intragranular_gas_swelling[0] = Sciantix_variables[9];
  Intergranular_bubble_concentration[0] = Sciantix_variables[10];
  Intergranular_atoms_per_bubble[0] = Sciantix_variables[11];
  Intergranular_vacancies_per_bubble[0] = Sciantix_variables[12];
  Intergranular_bubble_radius[0] = Sciantix_variables[13];
  Intergranular_bubble_area[0] = Sciantix_variables[14];
  Intergranular_bubble_volume[0] = Sciantix_variables[15];
  Intergranular_fractional_coverage[0] = Sciantix_variables[16];
  Intergranular_saturation_fractional_coverage[0] = Sciantix_variables[17];
  Intergranular_gas_swelling[0] = Sciantix_variables[18];
  Intergranular_fractional_intactness[0] = Sciantix_variables[19];
  Burn_up[0] = Sciantix_variables[20];
  Effective_burn_up[0] = Sciantix_variables[21];

  sf_resolution_rate = Sciantix_scaling_factors[0];
  sf_trapping_rate = Sciantix_scaling_factors[1];
  sf_nucleation_rate = Sciantix_scaling_factors[2];
  sf_diffusion_rate = Sciantix_scaling_factors[3];
}
