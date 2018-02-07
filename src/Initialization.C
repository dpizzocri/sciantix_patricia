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

/// Initialization
/// This routine initializes some global variables
/// to the values provided in input.

#include "Initialization.h"

void Initialization( )
{
  Grain_radius[1] = Initial_grain_radius;
  Temperature[1] = Temperature_input[0];
  Fissionrate[1] = Fissionrate_input[0];
}
