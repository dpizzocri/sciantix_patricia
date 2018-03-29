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

#include "IntraGranularGasSwelling.h"

void IntraGranularGasSwelling( )
{
  Intragranular_gas_swelling[1] = 4.0/3.0*Pi * Intragranular_bubble_concentration[1] * pow(Intragranular_bubble_radius[1], 3);
}
