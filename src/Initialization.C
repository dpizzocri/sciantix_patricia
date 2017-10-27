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

/// Initialization
/// This routine initializes some global variables
/// to the values provided in input.

#include "Initialization.h"

void Initialization( )
{
  Grain_radius[1] = Initial_grain_radius;
  Intergranular_bubble_concentration[1] = Initial_intergranular_bubble_concentration;

  Temperature[1] = Temperature_input[0];
  Fissionrate[1] = Fissionrate_input[0];
  Hydrostaticstress[1] = Hydrostaticstress[0];
}
