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
  Specificpower[0] = Specificpower[1];
  Hydrostaticstress[0] = Hydrostaticstress[1];
}