///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 0.1                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

/// InterGranularGasSwelling
/// This routine calculates the volumetric strain
/// caused by the presence of inter-granular
/// gas bubbles

#include "InterGranularGasSwelling.h"

void InterGranularGasSwelling( )
{
  const double surface_to_volume_ratio = 3.0 / Grain_radius[1];
  Intergranular_gas_swelling[1] = surface_to_volume_ratio * Intergranular_bubble_concentration[1] * Intergranular_bubble_volume[1];
}
