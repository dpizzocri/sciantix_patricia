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

/// Storage
/// This function stores values of the quantities of
/// interest calculated at the end of the current time step
/// and so defines the initial conditions for the next time step.

#include "Storage.h"

void Storage( )
{
  Temperature[0] = Temperature[1];
  Fissionrate[0] = Fissionrate[1];
  Hydrostaticstress[0] = Hydrostaticstress[1];
  Burn_up[0] = Burn_up[1];
  Effective_burn_up[0] = Effective_burn_up[1];
  Grain_radius[0] = Grain_radius[1];
  Gas_produced[0] = Gas_produced[1];
  Gas_grain[0] = Gas_grain[1];
  Gas_grain_solution[0] = Gas_grain_solution[1];
  Gas_grain_bubbles[0] = Gas_grain_bubbles[1];
  Gas_boundary[0] = Gas_boundary[1];
  Gas_grain_dislocations[0] = Gas_grain_dislocations[1];

  fannealing[0] = fannealing[1];

  Intragranular_bubble_concentration[0] = Intragranular_bubble_concentration[1];
  Intragranular_bubble_radius[0] = Intragranular_bubble_radius[1];
  Intragranular_bubble_concentration_at_dislocations[0] = Intragranular_bubble_concentration_at_dislocations[1];
  Intragranular_bubble_radius_at_dislocations[0] = Intragranular_bubble_radius_at_dislocations[1];
  Intragranular_atoms_per_bubble[0] = Intragranular_atoms_per_bubble[1];
  Intragranular_atoms_per_bubble_at_dislocations[0] = Intragranular_atoms_per_bubble_at_dislocations[1];
  Group_bubble_growth[0] = Group_bubble_growth[1];
  Intragranular_vacancies_per_bubble_at_dislocations[0] = Intragranular_vacancies_per_bubble_at_dislocations[1];
  Dislocation_density[0] = Dislocation_density[1];
  Intragranular_bubble_volume_at_dislocations[0] = Intragranular_bubble_volume_at_dislocations[1];

  Intergranular_bubble_concentration[0] = Intergranular_bubble_concentration[1];
  Intergranular_atoms_per_bubble[0] = Intergranular_atoms_per_bubble[1];
  Intergranular_vacancies_per_bubble[0] = Intergranular_vacancies_per_bubble[1];
  Intergranular_bubble_radius[0] = Intergranular_bubble_radius[1];
  Intergranular_bubble_area[0] = Intergranular_bubble_area[1];
  Intergranular_bubble_volume[0] = Intergranular_bubble_volume[1];
  Intergranular_fractional_coverage[0] = Intergranular_fractional_coverage[1];
  Intergranular_gas_swelling[0] = Intergranular_gas_swelling[1];
}
