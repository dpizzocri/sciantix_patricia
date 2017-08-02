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

#include "InputStorage.h"

void InputStorage( )
{
  Temperature[0] = Temperature[1];
  Fissionrate[0] = Fissionrate[1];
  Hydrostaticstress[0] = Hydrostaticstress[1];
  Burn_up[0] = Burn_up[1];
  Effective_burn_up[0] = Effective_burn_up[1];
  Grain_radius[0] = Grain_radius[1];
  Gas_grain[0] = Gas_grain[1];
  Gas_grain_solution[0] = Gas_grain_solution[1];
  Gas_grain_bubbles[0] = Gas_grain_bubbles[1];
  Gas_boundary[0] = Gas_boundary[1];
  Gas_grain_dislocations[0] = Gas_grain_dislocations[1];
  
  Intragranular_bubble_concentration[0] = Intragranular_bubble_concentration[1];
  Intragranular_bubble_radius[0] = Intragranular_bubble_radius[1];
  Intragranular_bubble_concentration_at_dislocations[0] = Intragranular_bubble_concentration_at_dislocations[1];
  Intragranular_bubble_radius_at_dislocations[0] = Intragranular_bubble_radius_at_dislocations[1];
  Atoms_per_bubble[0] = Atoms_per_bubble[1];
  Atoms_per_bubble_at_dislocations[0] = Atoms_per_bubble_at_dislocations[1];
  Group_bubble_growth[0] = Group_bubble_growth[1];
  Trapping_rate_at_dislocations[0] = Trapping_rate_at_dislocations[1];
}
