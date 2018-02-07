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

#include "InputStorage.h"

void InputStorage( )
{
  Temperature[0] = Temperature[1];
  Fissionrate[0] = Fissionrate[1];
  Hydrostaticstress[0] = Hydrostaticstress[1];

  Grain_radius[0] = Grain_radius[1];
  Gas_grain[0] = Gas_grain[1];
  Gas_grain_solution[0] = Gas_grain_solution[1];
  Gas_grain_bubbles[0] = Gas_grain_bubbles[1];
  Gas_boundary[0] = Gas_boundary[1];
}
