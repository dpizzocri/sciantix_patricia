///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//           L. Cognini                  //
///////////////////////////////////////////

#include "SetVariables.h"

void SetVariables(int Sciantix_options[], double Sciantix_history[], double Sciantix_variables[], double Sciantix_scaling_factors[], double Sciantix_diffusion_modes[])
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
  ifuel_reactor_type = Sciantix_options[15];

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
  He4[0] = Sciantix_variables[22];
  O16[0] = Sciantix_variables[23];
  Tl207[0] = Sciantix_variables[24];
  Tl208[0] = Sciantix_variables[25];
  Pb206[0] = Sciantix_variables[26];
  Pb207[0] = Sciantix_variables[27];
  Pb208[0] = Sciantix_variables[28];
  Pb210[0] = Sciantix_variables[29];
  Pb211[0] = Sciantix_variables[30];
  Pb212[0] = Sciantix_variables[31];
  Pb214[0] = Sciantix_variables[32];
  Bi210[0] = Sciantix_variables[33];
  Bi211[0] = Sciantix_variables[34];
  Bi212[0] = Sciantix_variables[35];
  Bi214[0] = Sciantix_variables[36];
  Po210[0] = Sciantix_variables[37];
  Po212[0] = Sciantix_variables[38];
  Po214[0] = Sciantix_variables[39];
  Po215[0] = Sciantix_variables[40];
  Po216[0] = Sciantix_variables[41];
  Po218[0] = Sciantix_variables[42];
  Rn219[0] = Sciantix_variables[43];
  Rn220[0] = Sciantix_variables[44];
  Rn222[0] = Sciantix_variables[45];
  Fr223[0] = Sciantix_variables[46];
  Ra223[0] = Sciantix_variables[47];
  Ra224[0] = Sciantix_variables[48];
  Ra226[0] = Sciantix_variables[49];
  Ra228[0] = Sciantix_variables[50];
  Ac227[0] = Sciantix_variables[51];
  Ac228[0] = Sciantix_variables[52];
  Th227[0] = Sciantix_variables[53];
  Th228[0] = Sciantix_variables[54];
  Th230[0] = Sciantix_variables[55];
  Th231[0] = Sciantix_variables[56];
  Th232[0] = Sciantix_variables[57];
  Th234[0] = Sciantix_variables[58];
  Pa231[0] = Sciantix_variables[59];
  Pa234[0] = Sciantix_variables[60];
  U234[0] = Sciantix_variables[61];
  U235[0] = Sciantix_variables[62];
  U236[0] = Sciantix_variables[63];
  U237[0] = Sciantix_variables[64];
  U238[0] = Sciantix_variables[65];
  Np237[0] = Sciantix_variables[66];
  Np238[0] = Sciantix_variables[67];
  Np239[0] = Sciantix_variables[68];
  Pu238[0] = Sciantix_variables[69];
  Pu239[0] = Sciantix_variables[70];
  Pu240[0] = Sciantix_variables[71];
  Pu241[0] = Sciantix_variables[72];
  Pu242[0] = Sciantix_variables[73];
  Pu243[0] = Sciantix_variables[74];
  Am241[0] = Sciantix_variables[75];
  Am242[0] = Sciantix_variables[76];
  Am242m[0] = Sciantix_variables[77];
  Am243[0] = Sciantix_variables[78];
  Am244[0] = Sciantix_variables[79];
  Cm242[0] = Sciantix_variables[80];
  Cm243[0] = Sciantix_variables[81];
  Cm244[0] = Sciantix_variables[82];
  Cm245[0] = Sciantix_variables[83];
  Fuel_density[0] = Sciantix_variables[84];
  Oxygen_to_metal_ratio[0] = Sciantix_variables[85];
  Helium_produced[0] = Sciantix_variables[86];
  Helium_grain[0] = Sciantix_variables[87];
  Helium_grain_solution[0] = Sciantix_variables[88];
  Helium_grain_bubbles[0] = Sciantix_variables[89];
  Helium_boundary[0] = Sciantix_variables[90];
  Helium_released[0] = Sciantix_variables[91];
  Initial_U235_enrichment = Sciantix_variables[92];
  Initial_Pu239_enrichment = Sciantix_variables[93];

  sf_resolution_rate = Sciantix_scaling_factors[0];
  sf_trapping_rate = Sciantix_scaling_factors[1];
  sf_nucleation_rate = Sciantix_scaling_factors[2];
  sf_diffusion_rate = Sciantix_scaling_factors[3];

  for(int i=0; i<40; ++i)
  {
    gas_grain_modes[i] = Sciantix_diffusion_modes[i];
  }
}
