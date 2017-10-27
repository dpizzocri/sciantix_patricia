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

#include "IntraGranularGasSwelling.h"

void IntraGranularGasSwelling( )
{
  Intragranular_gas_swelling[1] = 4.0/3.0*Pi * Intragranular_bubble_concentration[1] * pow(Intragranular_bubble_radius[1], 3);
}
